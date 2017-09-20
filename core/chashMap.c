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
  initCObject((CObject*)obj, CHashMap_NAME);
  obj->index = initCArrayList(newCArrayList(cobject_getCMemory((CObject*)obj)), size);
  carrayList_openAll(obj->index);
//  obj->cache = initCLinkedList(newCLinkedList(cobject_getCMemory((CObject*)obj)));
  return obj;
}

CHashMap* createCHashMap(int size) {
  return initCHashMap(newCHashMap(getCMemory()), size);
}

void freeCHashMap(void* obj) {
  CHashMap *mapObj = obj;

//  for(int i=0;i<carrayList_getLength(mapObj->index);i++) {
//    CLinkedList *o = (CLinkedList *)carrayList_get(mapObj->index,i);
//    for(int j=0;j<clinkedList_getLength(o);j++) {
//        CObject *p = clinkedList_get(o,i);
//    }
//  }

  releaseCObject((CObject*)mapObj->index);
  //releaseCObject((CObject*)mapObj->cache);
  freeCObject(obj);
}

CHashMap* chashMap_put(CHashMap *obj, CObject *keyObj, CObject *valueObj) {
  int hashCode = cobject_hashCode((CObject*)keyObj);
  int size = carrayList_getLength(obj->index);
  int key = hashCode % size;
  //
  //
  CObject* currentValue = carrayList_get(obj->index, key);
  if(currentValue == NULL) {
    currentValue = (CObject*)initCLinkedList(newCLinkedList(cobject_getCMemory((CObject*)obj)));
  //  clinkedList_addLast(obj->cache, cobject_downCounter(currentValue));
    carrayList_set(obj->index, key, cobject_downCounter(currentValue));
  }

  CLinkedList *list = (CLinkedList*)currentValue;
  int len = clinkedList_getLength(list);
  for(int i=0;i<len;i++) {
      CHashMapItem *item = (CHashMapItem *)clinkedList_get(list, i);
      if(0 != cobject_equals(item->key, keyObj)){
         //
         releaseCObject(item->value);
         cobject_upCounter(valueObj);
         //
         item->value = valueObj;
         return obj;
      }
  }

  CHashMapItem *item = initCHashMapItem(newCHashMapItem(cobject_getCMemory((CObject*)obj)), keyObj, valueObj);
  clinkedList_addLast((CLinkedList*)currentValue, cobject_downCounter((CObject*)item));
  return obj;
}

CObject* chashMap_get(CHashMap *obj, CObject *keyObj) {
  int hashCode = cobject_hashCode((CObject*)keyObj);
  int size = carrayList_getLength(obj->index);
  int key = hashCode % size;
  CObject* currentValue = carrayList_get(obj->index, key);
  if(currentValue == NULL) {
    return NULL;
  }

  CLinkedList *list = (CLinkedList*)currentValue;
  int len = clinkedList_getLength(list);
  for(int i=0;i<len;i++) {
      CHashMapItem *item = (CHashMapItem *)clinkedList_get(list, i);
      if(0 != cobject_equals(item->key, keyObj)){
          return item->value;
      }
  }
  return NULL;
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
  initCObject((CObject*)obj, CHashMapItem_NAME);
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
