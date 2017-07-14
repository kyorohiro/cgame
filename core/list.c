#include "object.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

ArrayList* newArrayList() {
  ArrayList *obj = calloc(1, sizeof(ArrayList));
  return obj;
}

ArrayList* initArrayList(ArrayList *obj, const char *name, int max) {
  initCObject((CObject*)obj, name);
  obj->length = 0;
  obj->max = max;
  obj->objects = (CObject**) calloc(max, sizeof(CObject*));
  obj->parent.funcFreeObj = freeArrayList;
  return obj;
}

void freeArrayList(void* obj) {
  if(obj == NULL) {
    return;
  }
  ArrayList *arrayListObj = (ArrayList *)obj;
  if(arrayListObj->objects != NULL) {
    free(arrayListObj->objects);
  }
  freeCObject(obj);
}

ArrayList* arrayList_grow(ArrayList* obj) {
  CObject**tmp = obj->objects;
  int tmpMax = obj->max;
  int max = tmpMax;
  int i = 0;
  obj->objects = calloc(max, sizeof(CObject));
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
  return obj;
}

ArrayList* arrayList_removeLast(ArrayList* obj) {
  if(obj->length<=0) {
    return obj;
  }
  arrayList_set(obj, obj->length, NULL);
  obj->length--;
  return obj;
}

CObject* arrayList_getLast(ArrayList* obj) {
  if(obj->length<=0) {
    return NULL;
  }
  return obj->objects[--obj->length];
}

CObject* arrayList_get(ArrayList* obj, int index) {
  if(obj->length>=index) {
    return NULL;
  }
  return obj->objects[index];
}

ArrayList* arrayList_set(ArrayList* obj, int index, CObject *item) {
  if(obj->length>=index) {
    return obj;
  }

  CObject *tmp = obj->objects[index];
  if(tmp != NULL) {
    obj->objects[index] = NULL;
    tmp->reference--;
  }
  obj->objects[index] = item;
  if(item != NULL) {
    item->reference++;
  }
  return obj;
}
