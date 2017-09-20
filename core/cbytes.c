#include "cbytes.h"
#include <string.h>
#include <stdio.h>

void _freeCBytes(void* obj);
CBytes* newCBytes(CMemory* cmemory) {
  CBytes* ret = cmemory_calloc(cmemory, 1, sizeof(CBytes));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCBytes;
  return ret;
}

CBytes* initCBytes(CBytes* obj, char *value, int length) {
  initCObject((CObject *)obj, CBytes_NAME);
  CMemory* memory = cobject_getCMemory((CObject *)obj);
  obj->length = length;
  obj->value = (char*)cmemory_calloc(memory, 1, sizeof(char)*obj->length);
  obj->parent.funcFree = _freeCBytes;
  if(value != NULL) {
    memcpy(obj->value, value, obj->length);
  }
  return obj;
}

CBytes* createCBytes(char *value, int length) {
  return initCBytes(newCBytes(getCMemory()), value, length);
}

void _freeCBytes(void* obj) {
  CObject *objObj = (CObject*)obj;
  CBytes *byeObj = (CBytes*)obj;
  if(byeObj->value != NULL) {
    cmemory_free(objObj->cmemory, byeObj->value);
  }
  freeCObject(obj);
}

int cbytes_getLength(CBytes* obj) {
  return obj->length;
}

char* cbytes_getBytes(CBytes* obj) {
  return obj->value;
}

CBytes* cbytes_setLength(CBytes* obj, int nextLength) {
  int prevLength = obj->length;
  if(nextLength <= prevLength) {
    obj->length = nextLength;
    return obj;
  }

  char* next = (char*)cmemory_calloc(obj->parent.cmemory, 1, sizeof(char)*nextLength);
  for(int i=0;i<prevLength;i++) {
    next[i] = obj->value[i];
  }

  if(obj->value != NULL) {
    cmemory_free(((CObject*)obj)->cmemory, obj->value);
  }

  obj->value = next;
  return obj;
}
