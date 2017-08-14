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
  initCObject((CObject*)obj, CAPP_NAME);
  snprintf(obj->title, sizeof(obj->title), "%s", "title");
  obj->width = 400;
  obj->height = 300;
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
}

void capp_draw(void) {
  //CGame *game = getCGame();
}

CApp* cgame_start(CApp* obj) {
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
  glutMainLoop();
  return obj;
}
