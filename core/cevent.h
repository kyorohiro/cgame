#ifndef _H_CEventDispatcher
#define _H_CEventDispatcher

#include "ccore_inner.h"
#include "cmemory.h"
#include "cobject.h"
#include "clinkedList.h"


typedef void (*CEventFuncOnEvent)(CObject* context, CObject* args);

typedef struct {
  CObject parent;
  CObject *context;
  CEventFuncOnEvent onEvent;
} CEventObserver;

CEventObserver* newCEventObserver(CMemory*);
CEventObserver* initCEventObserver(CEventObserver* obj, CObject *context, CEventFuncOnEvent onEvent);
CEventObserver* createCEventObserver(CObject *context, CEventFuncOnEvent onEvent);


// UTF8
typedef struct {
  CObject parent;
  CLinkedList *observers;
} CEventDispatcher;

CEventDispatcher* newCEventDispatcher(CMemory*);
CEventDispatcher* initCEventDispatcher(CEventDispatcher* obj);
CEventDispatcher* createCEventDispatcher(CEventDispatcher* obj);

CEventObserver* ceventDispatcher_addListener(CEventDispatcher* obj, CObject*context, CEventFuncOnEvent);
CEventDispatcher* ceventDispatcher_removeListener(CEventDispatcher* obj, CEventObserver* target);
CEventDispatcher* ceventDispatcher_dispatch(CEventDispatcher* obj, CObject* event);
#endif
