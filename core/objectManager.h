#ifndef _H_COBJECT_MANAGER
#define _H_COBJECT_MANAGER
#include "cobject.h"
#include "carrayList.h"
#include "cmemory.h"

#define COBJECTMANAGER_NAME "omg"

typedef struct {
  CObject parent;
  CArrayList *objects;
} CObjectManager;

CObjectManager* newCObjectManager(CMemory *mem);
CObjectManager* initCObjectManager(CObjectManager *obj);
CObjectManager* objectManager_addObject(CObjectManager *obj, CObject *item);
CObjectManager* objectManager_releaseAll(CObjectManager *obj);
CObjectManager* objectManager_releaseObject(CObjectManager *obj, CObject *item);
CObjectManager* getCObjectManager();

CObjectManager* objectManager_showInfo(CObjectManager *obj);

#endif
