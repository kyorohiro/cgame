#include "cobject.h"
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
  obj->funcFree = freeCObject;
  onMode(obj, COBJECT_MODE_FREEABLE);
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


CObject* _releaseCObject(CObject* obj, int isForce) {
  obj->reference--;
  if(isForce != 0 || (obj->reference<=0 && getMode(obj, COBJECT_MODE_FREEABLE) == 1)){
    CObjectFuncFree func = obj->funcFree;
    if(func != NULL) {
      func(obj);
    }
    return NULL;
  } else {
    return obj;
  }
}

CObject* releaseForceCObject(CObject* obj) {
  return  _releaseCObject(obj, 1);
}

CObject* releaseCObject(CObject* obj) {
  return  _releaseCObject(obj, 0);
}
