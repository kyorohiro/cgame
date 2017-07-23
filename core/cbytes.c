#include "cbytes.h"
#include <string.h>
#include <stdio.h>

void _freeCBytes(void* obj);
CBytes* newCBytes(CMemory* cmemory) {
  CBytes* ret = cmemory_calloc(cmemory, 1, sizeof(CBytes));
  ret->parent.cmemory = cmemory;
  return ret;
}

CBytes* initCBytes(CBytes* obj, char *value, int length) {
  initCObject((CObject *)obj, CBYTE_NAME);
  obj->length = length;
  obj->value = (char*)cmemory_calloc(obj->parent.cmemory, 1, sizeof(char)*obj->length);
  obj->parent.funcFree = _freeCBytes;
  memcpy(obj->value, value, obj->length);
  return obj;
}

void _freeCBytes(void* obj) {
  CObject *objObj = (CObject*)obj;
  CBytes *byeObj = (CBytes*)obj;
  if(byeObj->value != NULL) {
    cmemory_free(objObj->cmemory, byeObj->value);
  }
  freeCObject(obj);
}

int cbyte_getLength(CBytes* obj) {
  return obj->length;
}

char* cbyte_getBytes(CBytes* obj) {
  return obj->value;
}
