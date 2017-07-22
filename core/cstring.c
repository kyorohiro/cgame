#include "cstring.h"
#include <string.h>
#include <stdio.h>

CString* newCString(CMemory* cmemory) {
  CString* ret = cmemory_calloc(cmemory, 1, sizeof(CString));
  ret->parent.cmemory = cmemory;
  return ret;
}

CString* calcLength(CString* obj, char *value) {
  int byteLength = 0;
  int length = 0;
  int np =0;
  for(length=0;value[length] != 0;length++) {
    if(np == 0) {
      if((0xE0 & value[length]) == 0xC0) {
        np=2;
      }
      else if((0xF0 & value[length]) == 0xE0) {
        np=3;
      }
      else if((0xF8 & value[length]) == 0xF0) {
        np=4;
      }
      np--;
      byteLength++;
    } else {
      np--;
    }
  }
  obj->byteLength = byteLength;
  obj->length = length;
  return obj;
}

CString* initCString(CString* obj, char *value) {
  initCObject((CObject *)obj, CSTRING_NAME);
  calcLength(obj, value);
  obj->value = (char*)cmemory_calloc(obj->parent.cmemory, 1, sizeof(char)*obj->byteLength+1);
  memcpy(obj->value, value, obj->byteLength+1);
  return obj;
}
