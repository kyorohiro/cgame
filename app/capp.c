#include "app/capp.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/cbytesBuilder.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

//
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_opengl.h>
//
#ifdef PLATFORM_EMCC
#include <emscripten.h>
#endif

CApp* newCApp(CMemory* mem) {
  CApp * ret = cmemory_calloc(mem, 1, sizeof(CApp));
  ret->parent.cmemory = mem;
  return ret;
}

CApp* initCApp(CApp* obj, int width, int height) {
  CMemory* mem = obj->parent.cmemory;
  initCObject((CObject*)obj, CAPP_NAME);
  snprintf(obj->title, sizeof(obj->title), "%s", "title");
  obj->width = width;
  obj->height = height;
  obj->mouse = initCEventDispatcher(newCEventDispatcher(mem));
  obj->display = initCEventDispatcher(newCEventDispatcher(mem));
  obj->init = initCEventDispatcher(newCEventDispatcher(mem));
  //
  obj->mouseEvent = initCAppMouseEvent(newCAppMouseEvent(obj->parent.cmemory), 0, 0, 0);
  return obj;
}

CApp* defaultCApp = NULL;
CApp* getCApp() {
  if(defaultCApp == NULL) {
    defaultCApp = initCApp(newCApp(getCMemory()), 400, 300);
  }
  return defaultCApp;
}

CApp* createCApp(int width, int height) {
  CApp* ret = initCApp(newCApp(getCMemory()), width, height);
  if(defaultCApp == NULL) {
    defaultCApp = ret;
  }
  return ret;
}



void capp_draw(CApp* obj) {
//  glClear(GL_COLOR_BUFFER_BIT);
  CApp* appObj = obj;
  //printf("capp_draw\r\n");
  ceventDispatcher_dispatch(appObj->display, NULL);
  appObj->debugCount++;
  if(appObj->debugTime == 0){
   appObj->debugTime = capp_currentMilliSecound(appObj);
  }
  if(appObj->debugCount > 100) {
   appObj->debugCount = 0;
   double t = capp_currentMilliSecound(appObj);
   double v = t - appObj->debugTime;
   double x = v/1000.0;
   appObj->fps = (int)100/x;
  // printf("#>> %lf : %lf\r\n", x, 100/x);
   appObj->debugTime = t;
  }
}

void main_loop(void*args) {
  CApp *app = args;
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_MOUSEMOTION:
        app->mouseEvent->x = event.motion.x;
        app->mouseEvent->y = event.motion.y;
        ceventDispatcher_dispatch(app->mouse, (CObject*)app->mouseEvent);
        app->fpsCount = 100;
        break;
      case SDL_MOUSEBUTTONDOWN:
        app->mouseEvent->state = 1;
        app->fpsCount = 100;
        break;
      case SDL_MOUSEBUTTONUP:
        app->mouseEvent->state = 0;
        app->fpsCount = 100;
        break;
#ifdef PLATFORM_EMCC
#define USE_SDL_MOUSEWHEEL
#endif
#ifdef USE_SDL_2
#define USE_SDL_MOUSEWHEEL
#endif
#ifdef USE_SDL_MOUSEWHEEL
      case SDL_MOUSEWHEEL:
        app->fpsCount = 100;
        break;
#endif
      case SDL_QUIT:
        app->isQuit = 1;
    }
  }

  capp_draw(app);
  //
  // fps keeper
  //
  #ifdef PLATFORM_EMCC
  if(app->fpsCount == 0) {
    emscripten_pause_main_loop();
    emscripten_async_call(main_loop, app, 1000/5);
  } else if(app->fpsCount == 100){
    emscripten_resume_main_loop();
    app->fpsCount--;
  } else {
    app->fpsCount--;
  }
  #endif
}

CApp* capp_init(CApp* obj) {
  printf("main 0\n");
  //
  SDL_Init(SDL_INIT_EVERYTHING);
#ifdef USE_SDL_2
  obj->window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, obj->width, obj->height, SDL_WINDOW_OPENGL);
  if (!obj->window) {
    printf("failed to create window\n");
    return obj;
  }
  obj->renderer = SDL_CreateRenderer(obj->window, -1, 0);
#else
  obj->screen = SDL_SetVideoMode( obj->width, obj->height, 0, SDL_HWSURFACE|SDL_OPENGL| SDL_DOUBLEBUF );
  if (obj->screen == NULL) {
    printf("failed to create window\n");
    return obj;
  }
#endif

  ceventDispatcher_dispatch(obj->init, (CObject*)obj);
  return obj;
}

CApp* capp_loop(CApp* obj) {
  #ifdef PLATFORM_EMCC
    emscripten_set_main_loop_arg(main_loop, obj, 60, 1);
  #else
    int prevTime = SDL_GetTicks();
    int currentTime = SDL_GetTicks();
    int interval = 1000/60;
    do {
      int currentTime = SDL_GetTicks();
      main_loop(obj);
      //
      // fps keeper
      //
      if(obj->fpsCount == 0) {
        interval = 1000/5;
      } else if(obj->fpsCount == 100){
        interval = 1000/60+1;
        obj->fpsCount--;
      } else {
        obj->fpsCount--;
      }
      if((currentTime-prevTime) < interval) {
        SDL_Delay(interval-(currentTime-prevTime));
      } else {
        SDL_Delay(1);
      }
      prevTime = currentTime;

    } while(obj->isQuit == 0);
  #endif

  return obj;
}

CApp* capp_run(CApp* obj) {
  return capp_loop(capp_init(obj));
}

//
//
CApp* capp_addMouseEventListener(CApp* obj, CObject* context, CEventFuncOnEvent func) {
  printf("call add Mouse Listener capp \r\n");
  ceventDispatcher_addListener(obj->mouse, context, func);
  return obj;
}

CApp* capp_addDisplayEventListener(CApp* obj, CObject* context, CEventFuncOnEvent func) {
  printf("call add Display Listener capp \r\n");
  ceventDispatcher_addListener(obj->display, context, func);
  return obj;
}

CApp* capp_addInitEventListener(CApp* obj, CObject* context, CEventFuncOnEvent func) {
  printf("call add Init Listener capp \r\n");
  ceventDispatcher_addListener(obj->init, context, func);
  return obj;
}

CAppMouseEvent* capp_getCurrentMouseEvent(CApp* obj) {
  return obj->mouseEvent;
}

double capp_currentMilliSecound(CApp* obj) {
  #ifdef PLATFORM_EMCC
    return emscripten_get_now();
  #else
    return SDL_GetTicks();
  #endif
}

CApp* capp_postRedisplay(CApp* obj) {
  // glutPostRedisplay();
  obj->fpsCount = 100;
  #ifdef PLATFORM_EMCC
    //emscripten_async_call(main_loop, obj, 1000/60);
  #else
  #endif
  return obj;
}

CApp* capp_flushBuffers(CApp* obj) {
  // glutSwapBuffers();
  //SDL_GL_SwapWindow(obj->window);
#ifdef USE_SDL_2
  SDL_RenderPresent(obj->renderer);
#else
  SDL_GL_SwapBuffers();
#endif
  return obj;
}

void _freeCAppMouseEvent(void* obj) {
  freeCObject(obj);
}

CAppMouseEvent* newCAppMouseEvent(CMemory* mem) {
  CAppMouseEvent * ret = cmemory_calloc(mem, 1, sizeof(CAppMouseEvent));
  ret->parent.cmemory = mem;
  ret->parent.funcFree = _freeCAppMouseEvent;
  return ret;
}

CAppMouseEvent* initCAppMouseEvent(CAppMouseEvent* obj, int state, float x, float y) {
  initCObject((CObject*)obj, CAPP_EVENT_MOUSE);
  obj->state = state;
  obj->x = x;
  obj->y = y;
  return obj;
}

char* capp_getAssetsPath(CApp* obj, char* path, char* out) {
#ifdef PLATFORM_EMCC
  #ifdef USE_SDL_2
  char* basePath = SDL_GetBasePath();
  #else
  char* basePath = "/";
  #endif
#else
  char* basePath = "./";
#endif
  int baseLen = strlen(basePath);
  int pathLen = strlen(path);
  if(out == NULL) {
    out = cmemory_calloc(cobject_getCMemory((CObject*)obj), 1, (baseLen+pathLen+2));
  }
  int i=0;
  int j=0;
  for(i=0;i<baseLen;i++) {
    out[i] = basePath[i];
  }
  for(j=0;j<pathLen;j++) {
    out[i+j] = path[j];
  }
  out[i+j] ='\0';

  return out;
}
