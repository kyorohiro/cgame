
#include "cevent.h"


void _freeCEventDispatcher(void* obj);

CEventDispatcher* newCEventDispatcher(CMemory* cmemory) {
  CEventDispatcher* ret = cmemory_calloc(cmemory, 1, sizeof(CEventDispatcher));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCEventDispatcher;
  return ret;
}

CEventDispatcher* initCEventDispatcher(CEventDispatcher* obj) {
  initCObject((CObject *)obj, CEVENT_NAME);
  return obj;
}

void _freeCEventDispatcher(void* obj) {
  freeCObject(obj);
}

CEventDispatcher* ceventDispatcher_addListener(CEventDispatcher* obj, CObject*context, CEventDispatcherFuncOnEvent func) {
  return obj;
}
