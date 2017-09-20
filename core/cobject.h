#ifndef _H_CObject
#define _H_CObject

#include "ccore_inner.h"
#include "cmemory.h"

typedef void (*CObjectFuncFree)(void *obj);
typedef int (*CObjectFuncHashCode)(void *obj);
typedef int (*CObjectFuncCompareTo)(void *obj, void *src);
typedef int (*CObjectFuncEquals)(void *obj, void *src);

#define COBJECT_MODE_FREEABLE 0x01

typedef struct {
  char name[8];
  int reference;
  int mode;
  int index;
  CObjectFuncFree funcFree;
  CObjectFuncHashCode funcHashCode;
  CObjectFuncCompareTo funcCompareTo;
  CObjectFuncEquals funcEquals;
  CMemory* cmemory;
} CObject;

CObject* newCObject(CMemory*);
CObject* initCObject(CObject*obj, const char *name);
CObject* initCObjectRock(CObject*obj, const char *name);
CObject* createCObject();

CObject* cobject_updateName(CObject*obj, const char *name);
CObject* releaseCObject(CObject* obj);
CObject* releaseForceCObject(CObject* obj);
void freeCObject(void* obj);

CObject* cobject_upCounter(CObject* obj);
CObject* cobject_downCounter(CObject* obj);
CObject* cobject_onMode(CObject* obj, int mode);
CObject* cobject_offMode(CObject* obj, int mode);
int cobject_hashCode(CObject* obj);
int cobject_compareTo(CObject* obj, CObject* src);
int cobject_equals(CObject* obj, CObject* src);

int cobject_getMode(CObject* obj, int mode);

CMemory* cobject_getCMemory(CObject*obj);
#endif
