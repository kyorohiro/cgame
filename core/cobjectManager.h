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
CObjectManager* cobjectManager_addObject(CObjectManager *obj, CObject *item);
CObjectManager* cobjectManager_releaseAll(CObjectManager *obj);
CObjectManager* cobjectManager_releaseObject(CObjectManager *obj, CObject *item);
CObjectManager* getCObjectManager();

CObjectManager* cobjectManager_showInfo(CObjectManager *obj);

#endif
