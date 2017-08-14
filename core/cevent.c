
#include "cevent.h"
#include <stdio.h>

void _freeCEventObserver(void* obj);
void _freeCEventDispatcher(void* obj);


//
//
CEventObserver* newCEventObserver(CMemory* cmemory) {
  CEventObserver* ret = cmemory_calloc(cmemory, 1, sizeof(CEventObserver));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCEventObserver;
  return ret;
}

CEventObserver* initCEventObserver(CEventObserver* obj, CObject *context, CEventDispatcherFuncOnEvent onEvent) {
  initCObject((CObject *)obj, CEVENT_OBSERVER_NAME);
  obj->context = cobject_upCounter(context);
  obj->onEvent = onEvent;
  return obj;
}

void _freeCEventObserver(void* obj) {
  if(obj == NULL) {return;}
  CEventObserver* observerObj = obj;
  releaseCObject((CObject*)observerObj->context);
  freeCObject(obj);
}

//
//
CEventDispatcher* newCEventDispatcher(CMemory* cmemory) {
  CEventDispatcher* ret = cmemory_calloc(cmemory, 1, sizeof(CEventDispatcher));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCEventDispatcher;
  return ret;
}

CEventDispatcher* initCEventDispatcher(CEventDispatcher* obj) {
  initCObject((CObject *)obj, CEVENT_DISPATCHER_NAME);
  CMemory* cmemory = cobject_getCMemory((CObject*)obj);
  obj->observers = initCLinkedList(newCLinkedList(cmemory));
  return obj;
}

void _freeCEventDispatcher(void* obj) {
  if(obj == NULL) {return;}
  CEventDispatcher* dispatchObj = obj;
  releaseCObject((CObject*)dispatchObj->observers);
  freeCObject(obj);
}

CEventDispatcher* ceventDispatcher_addListener(CEventDispatcher* obj, CObject*context, CEventDispatcherFuncOnEvent func) {
  CMemory* cmemory = cobject_getCMemory((CObject*)obj);
  CEventObserver *observer = initCEventObserver(newCEventObserver(cmemory), context, func);
  clinkedList_addLast(obj->observers, observer);
  return obj;
}
