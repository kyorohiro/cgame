#include <stdio.h>
#include "app/capp.h"
#include "core/cstring.h"
#include "core/cmemory.h"
#include "app/cmixer.h"

int fps;
void _testOnDisplay(CObject* context, CObject* args) {
  glClearColor(1.0, 0.7, 0.7, 1.0);//rgba
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  CApp* appObj = getCApp();
  capp_postRedisplay(appObj);
  if(fps != appObj->fps) {
    fps = appObj->fps;
    printf("fps:%d;\r\n",fps);
  }
  //capp_flushBuffers(appObj);
}

int main(int argc, char** argv) {
  printf("capp 003 mixer sample");
  CApp* appObj = getCApp();
  CString *context = initCString(newCString(getCMemory()), "dummy");
  capp_addDisplayEventListener(appObj, (CObject*)context, _testOnDisplay);
  CMixer* mixer = initCMixer(newCMixer(getCMemory()));

  capp_run(appObj);
  return 0;
}
