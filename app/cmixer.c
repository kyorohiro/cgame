#include "cmixer.h"


void _freeCMixer(void* obj) {
  CObject *objObj = (CObject*)obj;
  CMixer *mixObj = (CMixer*)obj;
  freeCObject(obj);
}

CMixer* newCMixer(CMemory* mem) {
  CBytes* ret = cmemory_calloc(cmemory, 1, sizeof(CBytes));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCMixer;
}

CMixer* initCMixer(CMixer* obj){
  initCObject(obj, CMIXER_CHANNEL_NAME);
  return obj;
}
