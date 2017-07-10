#include "object.h"
#include <stdlib.h>
#include <stdio.h>

CObject* newCObject(const char *name) {
  CObject *ret = calloc(1,sizeof(CObject));
  snprintf(ret->name, sizeof(ret->name), "%s", name);
  ret->reference = 1;
  return ret;
}

CObject* freeObject(CObject* obj) {
  if(obj != NULL) {
    free(obj);
  }
  return NULL;
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
    free(obj);
    return NULL;
  } else {
    return obj;
  }
}
