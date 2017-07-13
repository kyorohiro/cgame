#ifndef _H_COBJECT_MANAGER
#define _H_COBJECT_MANAGER
#include "object.h"
#include "list.h"

typedef struct {
  CObject parent;
  ArrayList *objects;
} CObjectManager;

CObjectManager* newCObjectManager();
CObjectManager* initCObjectManager(CObjectManager *obj, const char *name);
CObjectManager* objectManager_addObject(CObjectManager *obj, CObject *item);

void freeCObjectManager(void* obj);
#endif
