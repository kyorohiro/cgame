#include "object.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

ArrayList* newArrayList(const char *name, int max) {
  ArrayList *obj = calloc(1, sizeof(ArrayList));
  initObject((CObject*)obj, name);
  obj->length = 0;
  obj->max = max;
  obj->objects = calloc(max, sizeof(CObject));
  obj->parent.funcFreeObj = freeArrayList;
  return obj;
}

void* freeArrayList(void* obj) {
  if(obj == NULL) {
    return NULL;
  }
  ArrayList *arrayListObj = (ArrayList *)obj;
  if(arrayListObj->objects != NULL) {
    free(arrayListObj->objects);
  }
  freeObject(obj);
  return NULL;
}
