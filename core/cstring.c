#include "cstring.h"
#include <string.h>
#include <stdio.h>

void _freeCString(void* obj);

CString* newCString(CMemory* cmemory) {
  CString* ret = cmemory_calloc(cmemory, 1, sizeof(CString));
  ret->parent.cmemory = cmemory;
  return ret;
}

void _freeCString(void* obj) {
  CObject *objObj = (CObject*)obj;
  CString *strObj = (CString*)obj;
  if(strObj->value != NULL) {
    cmemory_free(objObj->cmemory, strObj->value);
  }
  freeCObject(obj);
}

CString* calcLength(CString* obj, char *value) {
  int byteLength = 0;
  int length = 0;
  int np =0;
  for(length=0;value[length] != 0;length++) {
    if(np == 0) {
      if((0xE0 & value[length]) == 0xC0) {
        np=2-1;
      }
      else if((0xF0 & value[length]) == 0xE0) {
        np=3-1;
      }
      else if((0xF8 & value[length]) == 0xF0) {
        np=4-1;
      }
      byteLength++;
    } else {
      np--;
    }
  }
  obj->byteLength = byteLength+1;
  obj->length = length;
  return obj;
}

CString* initCString(CString* obj, char *value) {
  initCObject((CObject *)obj, CSTRING_NAME);
  calcLength(obj, value);
  obj->value = (char*)cmemory_calloc(obj->parent.cmemory, 1, sizeof(char)*obj->byteLength);
  obj->parent.funcFree = _freeCString;
  memcpy(obj->value, value, obj->byteLength);
  return obj;
}

int cstring_getLength(CString* obj) {
  return obj->length;
}

int cstring_getByteLength(CString* obj) {
  return obj->byteLength;
}

char* cstring_getBytes(CString* obj) {
  return obj->value;
}
