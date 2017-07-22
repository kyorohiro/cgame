#include "object.h"
#include "arraylist.h"
#include <stdio.h>
#include <stdlib.h>
#include "cmemory.h"

void freeArrayList(void* obj);
//
// ArrayList
//
ArrayList* newArrayList(CMemory* cmemory) {
  ArrayList* ret =  cmemory_calloc(cmemory,1, sizeof(ArrayList));
  ret->parent.cmemory = cmemory;
  return ret;
}

ArrayList* initArrayList(ArrayList *obj, int max) {
  initCObject((CObject*)obj, ARRAYLIST_NAME);
  obj->length = 0;
  obj->max = max;
  obj->objects = (CObject**) cmemory_calloc(obj->parent.cmemory,max, sizeof(CObject*));
  obj->parent.funcFree = freeArrayList;
  return obj;
}

void freeArrayList(void* obj) {

  int i=0;
  if(obj == NULL) {
    return;
  }
  ArrayList *arrayListObj = (ArrayList *)obj;

  for(i=0; i<arrayListObj->length;i++) {
    arrayList_set(arrayListObj, i, NULL);
  }
  if(arrayListObj->objects != NULL) {
    cmemory_free(arrayListObj->parent.cmemory,arrayListObj->objects);
  }
  freeCObject(obj);
}

ArrayList* arrayList_grow(ArrayList* obj) {
  CObject**tmp = obj->objects;
  int tmpMax = obj->max;
  int max = tmpMax;
  int i = 0;
  obj->objects = cmemory_calloc(obj->parent.cmemory,max, sizeof(CObject));
  for(i=0;i<obj->length;i++) {
    obj->objects[i] = tmp[i];
  }
  return obj;
}

ArrayList* arrayList_addLast(ArrayList* obj, CObject *item) {
  if(obj->length+1 >= obj->max) {
    arrayList_grow(obj);
  }
  obj->objects[obj->length++] = item;
  item->reference++;
  return obj;
}

ArrayList* arrayList_removeLast(ArrayList* obj) {
  if(obj->length<=0) {
    return obj;
  }
  CObject *item = arrayList_get(obj, obj->length-1);
  arrayList_set(obj, obj->length-1, NULL);
  obj->length--;
  item->reference--;

  return obj;
}

CObject* arrayList_getLast(ArrayList* obj) {
  if(obj->length<=0) {
    return NULL;
  }
  return obj->objects[obj->length-1];
}

CObject* arrayList_get(ArrayList* obj, int index) {
  if(obj->length<=index) {
    return NULL;
  }
  return obj->objects[index];
}

ArrayList* arrayList_set(ArrayList* obj, int index, CObject *item) {
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
