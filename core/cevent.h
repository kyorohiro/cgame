#ifndef _H_CEVENT
#define _H_CEVENT
//typedef int (*free)(int n);

#include "cmemory.h"
#include "cobject.h"


#define CEVENT_NAME "eve"

typedef void (*CEventDispatcherFuncOnEvent)(CObject* context, CObject* args);

// UTF8
typedef struct {
  CObject parent;
} CEventDispatcher;

CEventDispatcher* newCEventDispatcher(CMemory*);
CEventDispatcher* initCEventDispatcher(CEventDispatcher* obj);
CEventDispatcher* ceventDispatcher_addListener(CEventDispatcher* obj, CObject*context, CEventDispatcherFuncOnEvent);
#endif
