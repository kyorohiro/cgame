#include "object.h"
#include <stdlib.h>
#include <stdio.h>


CObject* newCObject(const char *name) {
  CObject *ret = calloc(1,sizeof(CObject));
  return initObject(ret, name);
}


CObject* initObject(CObject*obj, const char *name) {
  snprintf(obj->name, sizeof(obj->name), "%s", name);
  obj->reference = 1;
  obj->funcFreeObj = freeObject;
  return obj;
}

void freeObject(void* obj) {
  if(obj != NULL) {
    free(obj);
  }
}

CObject* upCounter(CObject* obj) {
  obj->reference++;
  return obj;
}

CObject* downCounter(CObject* obj) {
  obj->reference--;
  return obj;
}

CObject* releaseObject(CObject* obj) {
  if(!(obj->reference>0)){
    FuncFreeObj func = obj->funcFreeObj;
    if(func != NULL) {
      func(obj);
    }
    return NULL;
  } else {
    return obj;
  }
}
