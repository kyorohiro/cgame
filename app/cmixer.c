#include "cmixer.h"


void _freeCMixer(void* obj) {
  CObject *objObj = (CObject*)obj;
  CMixer *mixObj = (CMixer*)obj;
  freeCObject(obj);
}

CMixer* newCMixer(CMemory* cmemory) {
  CMixer* ret = (CMixer*)cmemory_calloc(cmemory, 1, sizeof(CMixer));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCMixer;
  return ret;
}

CMixer* initCMixer(CMixer* obj){
  initCObject((CObject*)obj, CMIXER_CHANNEL_NAME);
  return obj;
}
