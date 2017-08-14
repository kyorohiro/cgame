#ifndef _H_CEVENT
#define _H_CEVENT
//typedef int (*free)(int n);

#include "cmemory.h"
#include "cobject.h"


#define CEVENT_NAME "eve"

// UTF8
typedef struct {
  CObject parent;
} CEvent;

CEvent* newCEvent(CMemory*);
CEvent* initCEvent(CEvent* obj);
#endif
