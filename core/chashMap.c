#include "cobject.h"
#include "clinkedList.h"
#include "chashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include "cmemory.h"

void freeCHashMap(void* obj);
void freeCHashMapItem(void* obj);
CHashMap* newCHashMap(CMemory* cmemory) {
  CHashMap* ret = cmemory_calloc(cmemory, 1, sizeof(CHashMap));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = freeCHashMap;
  return ret;
}

CHashMap* initCHashMap(CHashMap *obj, int size) {
  initCObject((CObject*)obj, CHASHMAP_NAME);
  obj->index = initCArrayList(newCArrayList(cobject_getCMemory((CObject*)obj)), size);
  carrayList_openAll(obj->index);
  return obj;
}

void freeCHashMap(void* obj) {
  CHashMap *mapObj = obj;
//  printf("#>#%d\n", ((CObject*)mapObj->index)->reference);
  releaseCObject((CObject*)mapObj->index);

  freeCObject(obj);
}

CHashMap* chashMap_put(CHashMap *obj, CObject *key, CObject *value) {
  int hashCode = cobject_hashCode((CObject*)key);

  return obj;
}

//
//
//

CHashMapItem* newCHashMapItem(CMemory* cmemory) {
  CHashMapItem* ret = cmemory_calloc(cmemory, 1, sizeof(CHashMapItem));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = freeCHashMapItem;
  return ret;
}

CHashMapItem* initCHashMapItem(CHashMapItem *obj, CObject *key, CObject *value) {
  obj->key = cobject_upCounter(key);
  obj->value = cobject_upCounter(value);
  return obj;
}

void freeCHashMapItem(void* obj) {
  CHashMapItem* itemObj = (CHashMapItem*)obj;
  releaseCObject(itemObj->key);
  releaseCObject(itemObj->value);
  freeCObject(obj);
}
