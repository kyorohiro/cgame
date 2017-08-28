#include "app2/capp.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/cbytesBuilder.h"
#include <stdio.h>
#include <emscripten.h>
#include <math.h>

//
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_opengl.h>
//
CApp* newCApp(CMemory* mem) {
  CApp * ret = cmemory_calloc(mem, 1, sizeof(CApp));
  ret->parent.cmemory = mem;
  return ret;
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
  return obj;
}

CApp* defaultCApp = NULL;
CApp* getCApp() {
  if(defaultCApp == NULL) {
    defaultCApp = initCApp(newCApp(getCMemory()));
  }
  return defaultCApp;
}

void capp_special(int key, int x, int y) {
  printf(">special key:%d, x:%d, y:%d\r\n", key, x, y);
}

void capp_keyboard (unsigned char key,int x, int y) {
  printf(">keyboard key:%c, x:%d, y:%d\r\n", key, x, y);
}

void capp_mouse_motion_a (int state, int x, int y) {
  int stateTmp = 0;
  if(state == 0) {
    stateTmp = 1;
  }
  CApp* appObj = getCApp();
  if(appObj->mouseEvent == NULL) {
    appObj->mouseEvent = newCAppMouseEvent(appObj->parent.cmemory);
    initCAppMouseEvent(appObj->mouseEvent, state, x, y);
  }
  else if(appObj->parent.reference > 1) {
    releaseCObject((CObject *)appObj);
    appObj->mouseEvent = newCAppMouseEvent(appObj->parent.cmemory);
    initCAppMouseEvent(appObj->mouseEvent, state, x, y);
  }
  else {
    appObj->mouseEvent->state = stateTmp;
    appObj->mouseEvent->x = x;
    appObj->mouseEvent->y = y;
  }
  ceventDispatcher_dispatch(appObj->mouse, (CObject*)appObj->mouseEvent);
}

void capp_mouse (int button, int state,int x, int y) {
  printf(">mouse button:%c, xstate:%d x:%d, y:%d\r\n", button, state, x, y);
  capp_mouse_motion_a (state, x, y);
}

void capp_mouseM (int x, int y) {
  capp_mouse_motion_a (1, x, y);
}

void capp_mousePM (int x, int y) {
  capp_mouse_motion_a (0, x, y);
}

void capp_draw(void) {
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

CApp* capp_run(CApp* obj) {
  printf("main 0\n");
  CApp* appObj = getCApp();
  char *argv = "test";
  //
    printf("main 1\n");
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* window;
  SDL_GLContext glContext;
  printf("main 2\n");

  //SDL_Renderer* renderer;
  //SDL_CreateWindowAndRenderer(600, 400, 0, &window, &renderer);
  window = SDL_CreateWindow("sdlglshader", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
  glContext = SDL_GL_CreateContext(window);
  /*
  glutInit(0, &argv);
  glutInitWindowSize(appObj->width, appObj->height);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("es2gears");
  */
  glViewport(0, 0, appObj->width, appObj->height);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.9f, 1.0f, 0.9f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(window);
/*
  glutDisplayFunc(capp_draw);
  glutSpecialFunc(capp_special);
  glutKeyboardFunc(capp_keyboard);
  glutMouseFunc(capp_mouse);
  glutMotionFunc(capp_mouseM);
  glutPassiveMotionFunc(capp_mousePM);
*/
  ceventDispatcher_dispatch(appObj->init, (CObject*)obj);
/*
  glutMainLoop();
  */
  return obj;
}

//
//
CApp* capp_addMouseEventListener(CApp* obj, CObject* context, CEventFuncOnEvent func) {
  ceventDispatcher_addListener(obj->mouse, context, func);
  return obj;
}

CApp* capp_addDisplayEventListener(CApp* obj, CObject* context, CEventFuncOnEvent func) {
  printf("call add Listener capp \r\n");
  ceventDispatcher_addListener(obj->display, context, func);
  return obj;
}

CApp* capp_addInitEventListener(CApp* obj, CObject* context, CEventFuncOnEvent func) {
  printf("call add Listener capp \r\n");
  ceventDispatcher_addListener(obj->init, context, func);
  return obj;
}

CAppMouseEvent* capp_getCurrentMouseEvent(CApp* obj) {
  return obj->mouseEvent;
}

double capp_currentMilliSecound(CApp* obj) {
  return emscripten_get_now();
}

CApp* capp_postRedisplay(CApp* obj) {
  /*
  glutPostRedisplay();
  */
  return obj;
}

CApp* capp_flushBuffers(CApp* obj) {
  /*
  glutSwapBuffers();
  */
  return obj;
}
//
//
//
//
// Mouse Event
//
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
