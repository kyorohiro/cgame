#include "capp.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/cbytesBuilder.h"
#include <stdio.h>

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

void capp_mouse (int button, int state,int x, int y) {
  printf(">mouse button:%c, xstate:%d x:%d, y:%d\r\n", button, state, x, y);
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
    appObj->mouseEvent->state = state;
    appObj->mouseEvent->x = x;
    appObj->mouseEvent->y = y;
  }
  ceventDispatcher_dispatch(appObj->mouse, (CObject*)appObj->mouseEvent);

}

void capp_draw(void) {
//  printf("capp_draw\n");
  CApp* appObj = getCApp();
  ceventDispatcher_dispatch(appObj->display, NULL);
//  glutSwapBuffers();
//  glutPostRedisplay();
}

CApp* capp_run(CApp* obj) {
  printf("main\n");
  CApp* appObj = getCApp();
  char *argv = "test";
  glutInit(0, &argv);
  glutInitWindowSize(appObj->width, appObj->height);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("es2gears");
  glClearColor(0.9f, 1.0f, 0.9f, 1.0f);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc(capp_draw);
  glutSpecialFunc(capp_special);
  glutKeyboardFunc(capp_keyboard);
  glutMouseFunc(capp_mouse);

  ceventDispatcher_dispatch(appObj->init, (CObject*)obj);

  glutMainLoop();
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
