
#include "cevent.h"


void _freeCEvent(void* obj);

CEvent* newCEvent(CMemory* cmemory) {
  CEvent* ret = cmemory_calloc(cmemory, 1, sizeof(CEvent));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCEvent;
  return ret;
}

CEvent* initCEvent(CEvent* obj) {
  initCObject((CObject *)obj, CEVENT_NAME);
  return obj;
}

void _freeCEvent(void* obj) {
  freeCObject(obj);
}
