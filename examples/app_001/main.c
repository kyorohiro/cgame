#include <stdio.h>
#include "app/capp.h"
#include "core/cstring.h"
#include "core/cmemory.h"


void _testOnDisplay(CObject* context, CObject* args) {
  CApp* appObj = getCApp();
  capp_postRedisplay(appObj);
  capp_flushBuffers(appObj);
}

int main(int argc, char** argv) {
  printf("test");
  CApp* appObj = getCApp();
  CString *context = initCString(newCString(getCMemory()), "dummy");
  capp_addDisplayEventListener(appObj, (CObject*)context, _testOnDisplay);
  capp_run(appObj);

  return 0;
}
