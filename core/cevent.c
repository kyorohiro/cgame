
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

CEventObserver* initCEventObserver(CEventObserver* obj, CObject *context, CEventFuncOnEvent onEvent) {
  initCObject((CObject *)obj, CEventObserver_NAME);
  obj->context = cobject_upCounter(context);
  obj->onEvent = onEvent;
  return obj;
}

CEventObserver* createCEventObserver(CObject *context, CEventFuncOnEvent onEvent) {
  return initCEventObserver(newCEventObserver(getCMemory()), context, onEvent);
}

void _freeCEventObserver(void* obj) {
  if(obj == NULL) {return;}
  CEventObserver* observerObj = obj;
//  printf(">x> %d \r\n", ((CObject*)observerObj)->reference);
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
  initCObject((CObject *)obj, CEventDispatcher_NAME);
  CMemory* cmemory = cobject_getCMemory((CObject*)obj);
  obj->observers = initCLinkedList(newCLinkedList(cmemory));
  return obj;
}

CEventDispatcher* createCEventDispatcher(CEventDispatcher* obj) {
  return initCEventDispatcher(newCEventDispatcher(getCMemory()));
}

void _freeCEventDispatcher(void* obj) {
  if(obj == NULL) {return;}
  CEventDispatcher* dispatchObj = obj;
  releaseCObject((CObject*)dispatchObj->observers);
  freeCObject(obj);
}

CEventObserver* ceventDispatcher_addListener(CEventDispatcher* obj, CObject*context, CEventFuncOnEvent func) {
  printf("call add Listener \r\n");
  CMemory* cmemory = cobject_getCMemory((CObject*)obj);
  CEventObserver *observer = initCEventObserver(newCEventObserver(cmemory), context, func);
  cobject_downCounter((CObject*)observer);
  clinkedList_addLast(obj->observers, (CObject*)observer);
  return observer;
}

CEventDispatcher* ceventDispatcher_removeListener(CEventDispatcher* obj, CEventObserver* target) {
  CLinkedList* list = obj->observers;
  int len = clinkedList_getLength(list);
  CEventObserver *observer;
  for(int i=0; i< len; i++) {
    observer = (CEventObserver*)clinkedList_get(list, i);
    if(0 != cobject_equals((CObject*)observer, (CObject*)target)) {
      clinkedList_remove(list, i);
      return obj;
    }
  }
  return obj;
}

CEventDispatcher* ceventDispatcher_dispatch(CEventDispatcher* obj, CObject* event) {
  //printf("call dispatch \r\n");
  CLinkedList* list = obj->observers;
  int len = clinkedList_getLength(list);
  CEventObserver *observer;
  //printf("dispatch %d\r\n", len);
  for(int i=0; i< len; i++) {
    //printf("dispatch %d\r\n",i);
    observer = (CEventObserver*)clinkedList_get(list, i);
    observer->onEvent(observer->context, event);
  }
  return obj;
}
