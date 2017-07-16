#include "object.h"
#include <stdlib.h>
#include <stdio.h>
#include "cmemory.h"

CObject* newCObject(CMemory* cmemory) {
  CObject *ret = cmemory_calloc(cmemory, 1,sizeof(CObject));
  ret->cmemory = cmemory;
  return ret;
}

CObject* initCObject(CObject*obj, const char *name) {
  snprintf(obj->name, sizeof(obj->name), "%s", name);
  obj->reference = 1;
  obj->funcFreeObj = freeCObject;
  obj->mode = (obj->mode & (~COBJECT_MODE_FREEABLE));
  return obj;
}

void freeCObject(void* obj) {
  if(obj != NULL) {
    cmemory_free(((CObject*)obj)->cmemory, obj);
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

CObject* onMode(CObject* obj, int mode) {
  obj->mode = (obj->mode & (~mode)) | mode;
  return obj;
}

CObject* offMode(CObject* obj, int mode) {
  obj->mode = (obj->mode & (~mode));
  return obj;
}

int getMode(CObject* obj, int mode) {
  if((obj->mode & mode) != 0) {
    return 1;
  } else {
    return 0;
  }
}

CObject* releaseCObject(CObject* obj) {
  obj->reference--;
  if(!(obj->reference>0) && obj->mode == 2){
    FuncFreeObj func = obj->funcFreeObj;
    if(func != NULL) {
      func(obj);
    }
    return NULL;
  } else {
    return obj;
  }
}
