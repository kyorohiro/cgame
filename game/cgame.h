#ifndef _H_OBJECT
#define _H_OBJECT
//typedef int (*free)(int n);

#include "cmemory.h"

#define COBJECT_MODE_FREEABLE 0x01
#define COBJECT_NAME "obj";

typedef void (*FuncFreeObj)(void *obj);
typedef struct {
  char name[12];
  int reference;
  int mode;
  int index;
  FuncFreeObj funcFreeObj;
  CMemory* cmemory;
} CObject;

CObject* newCObject(CMemory*);
CObject* initCObject(CObject*obj, const char *name);
void freeCObject(void* obj);
CObject* upCounter(CObject* obj);
CObject* downCounter(CObject* obj);
CObject* releaseCObject(CObject* obj);
CObject* releaseForceCObject(CObject* obj);
CObject* onMode(CObject* obj, int mode);
CObject* offMode(CObject* obj, int mode);
int getMode(CObject* obj, int mode);
#endif
