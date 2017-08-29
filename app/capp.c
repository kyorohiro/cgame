#include "app/capp.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/cbytesBuilder.h"
#include <stdio.h>
#include <math.h>

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

CApp* defaultCApp = NULL;
CApp* getCApp() {
  if(defaultCApp == NULL) {
    defaultCApp = initCApp(newCApp(getCMemory()));
  }
  return defaultCApp;
}

CApp* initCApp(CApp* obj) {
  CMemory* mem = obj->parent.cmemory;
  initCObject((CObject*)obj, CAPP_NAME);
  snprintf(obj->title, sizeof(obj->title), "%s", "title");
  obj->width = 400;
  obj->height = 300;
  obj->mouse = initCEventDispatcher(newCEventDispatcher(mem));
  obj->display = initCEventDispatcher(newCEventDispatcher(mem));
  obj->init = initCEventDispatcher(newCEventDispatcher(mem));
  //
  obj->mouseEvent = initCAppMouseEvent(newCAppMouseEvent(obj->parent.cmemory), 0, 0, 0);
  return obj;
}

void capp_draw(CApp* obj) {
//  glClear(GL_COLOR_BUFFER_BIT);
  CApp* appObj = getCApp();
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
        break;
      case SDL_MOUSEBUTTONDOWN:
        app->mouseEvent->state = 1;
        break;
      case SDL_MOUSEBUTTONUP:
        app->mouseEvent->state = 0;
        break;
      case SDL_MOUSEWHEEL:
        break;
      case SDL_QUIT:
        app->isQuit = 1;
    }
  }
  capp_draw(app);
}

CApp* capp_run(CApp* obj) {
  printf("main 0\n");
  //
  SDL_Init(SDL_INIT_EVERYTHING);
//  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
//  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  obj->window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, obj->width, obj->height, SDL_WINDOW_OPENGL);
  if (!obj->window) {
    printf("failed to create window\n");
    return obj;
  }
  obj->renderer = SDL_CreateRenderer(obj->window, -1, 0);

  //SDL_GLContext glContext;
  //glContext = SDL_GL_CreateContext(window);
  //if (!glContext) {
  //  printf("failed to create glContext\n");
  //  return obj;
  //}

  ceventDispatcher_dispatch(obj->init, (CObject*)obj);

  #ifdef PLATFORM_EMCC
    emscripten_set_main_loop_arg(main_loop, obj, 60, 1);
  #else
    int prevTime = SDL_GetTicks();
    int currentTime = SDL_GetTicks();
    int interval = 1000/60;
    do {
      int currentTime = SDL_GetTicks();
      main_loop(obj);

      if(currentTime-prevTime < interval) {
        SDL_Delay(interval-(currentTime-prevTime));
      } else {
        SDL_Delay(1);
      }
      prevTime = currentTime;

    } while(obj->isQuit == 0);
  #endif

  return obj;
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
  return obj;
}

CApp* capp_flushBuffers(CApp* obj) {
  // glutSwapBuffers();
  //SDL_GL_SwapWindow(obj->window);
  SDL_RenderPresent(obj->renderer);
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
