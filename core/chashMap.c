#include "cobject.h"
#include "clinkedList.h"
#include "chashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include "cmemory.h"

void freeCHashMap(void* obj);
CHashMap* newCHashMap(CMemory* cmemory) {
  CHashMap* ret = cmemory_calloc(cmemory, 1, sizeof(CHashMap));
  ret->parent.cmemory = cmemory;
  return ret;
}

CHashMap* initCHashMap(CHashMap *obj) {
  initCObject((CObject*)obj, CHASHMAP_NAME);
  obj->index = newCArrayList(cobject_getCMemory((CObject*)obj));
  return obj;
}

void freeCHashMap(void* obj) {
  CHashMap *mapObj = obj;
  releaseCObject((CObject*)mapObj->index);
  freeCObject(obj);
}
