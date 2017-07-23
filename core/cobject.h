#ifndef _H_OBJECT
#define _H_OBJECT
//typedef int (*free)(int n);

#include "cmemory.h"

#define COBJECT_MODE_FREEABLE 0x01
#define COBJECT_NAME "obj"

typedef void (*CObjectFuncFree)(void *obj);
typedef int (*CObjectFuncHashCode)(void *obj);
typedef int (*CObjectFuncCompareTo)(void *obj, void *src);
typedef int (*CObjectFuncEquals)(void *obj, void *src);

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
CObject* cobject_updateName(CObject*obj, const char *name);

void freeCObject(void* obj);
CObject* upCounter(CObject* obj);
CObject* downCounter(CObject* obj);
CObject* releaseCObject(CObject* obj);
CObject* releaseForceCObject(CObject* obj);
CObject* onMode(CObject* obj, int mode);
CObject* offMode(CObject* obj, int mode);
int cobject_hashCode(CObject* obj);
int cobject_compareTo(CObject* obj, CObject* src);
int cobject_equals(CObject* obj, CObject* src);


int getMode(CObject* obj, int mode);
#endif
