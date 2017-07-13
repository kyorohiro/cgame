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
  obj->objects = calloc(max, sizeof(CObject));
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

ArrayList* add(ArrayList* obj, CObject *item) {
  return NULL;
}
