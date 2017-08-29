#include <stdio.h>
#include "app/capp.h"
#include "core/cstring.h"
#include "core/cmemory.h"


int fps;
CApp* appObj;

void _onInit(CObject* context, CObject* args) {
  printf("onInit\r\n");
  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, appObj->width, appObj->height);
  glClearColor(1.0, 0.7, 0.7, 1.0);//rgba
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void _onDisplay(CObject* context, CObject* args) {
  capp_postRedisplay(appObj);
  if(fps != appObj->fps) {
    fps = appObj->fps;
    printf("fps:%d;\r\n",fps);
  }
  //capp_flushBuffers(appObj);
}
int main(int argc, char** argv) {
  printf("capp sample");
  appObj = initCApp(newCApp(getCMemory()), 400, 300);
  CString *context = initCString(newCString(getCMemory()), "dummy");
  capp_addDisplayEventListener(appObj, (CObject*)context, _onDisplay);
  capp_addInitEventListener(appObj,  (CObject*)context, _onInit);
  capp_run(appObj);
  return 0;
}
