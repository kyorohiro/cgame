#ifndef _H_CObjectManager
#define _H_CObjectManager

#include "ccore_inner.h"
#include "cmemory.h"
#include "cobject.h"
#include "carrayList.h"


typedef struct {
  CObject parent;
  CArrayList *objects;
} CObjectManager;

CObjectManager* newCObjectManager(CMemory *mem);
CObjectManager* initCObjectManager(CObjectManager *obj);
CObjectManager* createCObjectManager();

CObjectManager* cobjectManager_addObject(CObjectManager *obj, CObject *item);
CObjectManager* cobjectManager_releaseAll(CObjectManager *obj);
CObjectManager* cobjectManager_releaseObject(CObjectManager *obj, CObject *item);
CObjectManager* getCObjectManager();

CObjectManager* cobjectManager_showInfo(CObjectManager *obj);

#endif
