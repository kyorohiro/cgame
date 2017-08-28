#include <stdio.h>
#include "app/capp.h"
#include "core/cstring.h"
#include "core/cmemory.h"

int fps;
void _testOnDisplay(CObject* context, CObject* args) {
  CApp* appObj = getCApp();
  capp_postRedisplay(appObj);
  if(fps != appObj->fps) {
    fps = appObj->fps;
    printf("fps:%d;\r\n",fps);
  }
  //capp_flushBuffers(appObj);
}

int main(int argc, char** argv) {
  printf("capp sample");
  CApp* appObj = getCApp();
  CString *context = initCString(newCString(getCMemory()), "dummy");
  capp_addDisplayEventListener(appObj, (CObject*)context, _testOnDisplay);
  capp_run(appObj);
  return 0;
}
