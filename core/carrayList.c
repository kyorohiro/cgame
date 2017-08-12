#include "cobject.h"
#include "carrayList.h"
#include <stdio.h>
#include <stdlib.h>
#include "cmemory.h"

void freeCArrayList(void* obj);

//
// CArrayList
//
CArrayList* newCArrayList(CMemory* cmemory) {
  CArrayList* ret =  cmemory_calloc(cmemory,1, sizeof(CArrayList));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = freeCArrayList;
  return ret;
}

CArrayList* initCArrayList(CArrayList *obj, int max) {
  initCObject((CObject*)obj, CcarrayList_NAME);
  obj->length = 0;
  obj->max = max;
  obj->objects = (CObject**) cmemory_calloc(obj->parent.cmemory,max, sizeof(CObject*));
//  obj->parent.funcFree = freeCArrayList;
  return obj;
}

void freeCArrayList(void* obj) {

  int i=0;
  if(obj == NULL) {
    return;
  }
  CArrayList *CArrayListObj = (CArrayList *)obj;

  for(i=0; i<CArrayListObj->length;i++) {
    carrayList_set(CArrayListObj, i, NULL);
  }
  if(CArrayListObj->objects != NULL) {
    cmemory_free(CArrayListObj->parent.cmemory,CArrayListObj->objects);
  }
  freeCObject(obj);
}

CArrayList* carrayList_grow(CArrayList* obj) {
  CObject**tmp = obj->objects;
  int tmpMax = obj->max;
  int max = tmpMax;
  int i = 0;
  obj->objects = cmemory_calloc(obj->parent.cmemory,max, sizeof(CObject));
  for(i=0;i<obj->length;i++) {
    obj->objects[i] = tmp[i];
  }
  cmemory_free(((CObject*)obj)->cmemory, tmp);
  return obj;
}

CArrayList* carrayList_addLast(CArrayList* obj, CObject *item) {
  if(obj->length+1 >= obj->max) {
    carrayList_grow(obj);
  }
  obj->objects[obj->length++] = item;
  item->reference++;
  return obj;
}

CArrayList* carrayList_removeLast(CArrayList* obj) {
  if(obj->length<=0) {
    return obj;
  }
  CObject *item = carrayList_get(obj, obj->length-1);
  carrayList_set(obj, obj->length-1, NULL);
  obj->length--;
  item->reference--;

  return obj;
}

CObject* carrayList_getLast(CArrayList* obj) {
  if(obj->length<=0) {
    return NULL;
  }
  return obj->objects[obj->length-1];
}

CObject* carrayList_get(CArrayList* obj, int index) {
  if(obj->length<=index) {
    return NULL;
  }
  return obj->objects[index];
}

CArrayList* carrayList_set(CArrayList* obj, int index, CObject *item) {
  if(obj->length <= index) {
    return obj;
  }

  CObject *tmp = obj->objects[index];
  if(tmp != NULL) {
    obj->objects[index] = NULL;
    releaseCObject(tmp);
  }
  obj->objects[index] = item;
  if(item != NULL) {
    item->reference++;
  }
  return obj;
}

int carrayList_getLength(CArrayList* obj) {
  return obj->length;
}
