#ifndef _H_CEVENT
#define _H_CEVENT
//typedef int (*free)(int n);

#include "cmemory.h"
#include "cobject.h"
#include "clinkedList.h"


#define CEVENT_NAME "eve"
#define CEVENT_OBSERVER_NAME "evo"
#define CEVENT_DISPATCHER_NAME "evd"

typedef void (*CEventDispatcherFuncOnEvent)(CObject* context, CObject* args);

typedef struct {
  CObject parent;
  CObject *context;
  CEventDispatcherFuncOnEvent onEvent;
} CEventObserver;

CEventObserver* newCEventObserver(CMemory*);
CEventObserver* initCEventObserver(CEventObserver* obj, CObject *context, CEventDispatcherFuncOnEvent onEvent);


// UTF8
typedef struct {
  CObject parent;
  CLinkedList *observers;
} CEventDispatcher;

CEventDispatcher* newCEventDispatcher(CMemory*);
CEventDispatcher* initCEventDispatcher(CEventDispatcher* obj);
CEventDispatcher* ceventDispatcher_addListener(CEventDispatcher* obj, CObject*context, CEventDispatcherFuncOnEvent);
#endif
