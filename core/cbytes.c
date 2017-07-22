#include "cstring.h"
#include <string.h>
#include <stdio.h>

CBytes* newCBytes(CMemory* cmemory) {
  CBytes* ret = cmemory_calloc(cmemory, 1, sizeof(CBytes));
  ret->parent.cmemory = cmemory;
  return ret;
}

CBytes* initCBytes(CBytes* obj, char *value, int length) {
  initCObject((CObject *)obj, CSTRING_NAME);
  obj->length = length;
  obj->value = (char*)cmemory_calloc(obj->parent.cmemory, 1, sizeof(char)*obj->length);
  memcpy(obj->value, value, obj->byteLength);
  return obj;
}
