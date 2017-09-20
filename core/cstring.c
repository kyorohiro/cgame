#include "cstring.h"
#include <string.h>
#include <stdio.h>


void _freeCString(void* obj);

CString* newCString(CMemory* cmemory) {
  CString* ret = cmemory_calloc(cmemory, 1, sizeof(CString));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCString;
  return ret;
}

CString* createCString(char *value) {
  return initCString(newCString(getCMemory()), value);
}

CString* createCStringWithLength(char *value, int byteLength) {
  return initCStringWithLength(newCString(getCMemory()), value, byteLength);
}

void _freeCString(void* obj) {
  CObject *objObj = (CObject*)obj;
  CString *strObj = (CString*)obj;
  if(strObj->value != NULL) {
    cmemory_free(objObj->cmemory, strObj->value);
  }
  freeCObject(obj);
}

CString* calcLength(CString* obj, char *value, int byteLengthSrc) {
  int byteLength = 0;
  int length = 0;
  int np =0;
  for(byteLength=0;;byteLength++) {
    if(byteLengthSrc < 0 && value[byteLength] == 0) {
      break;
    } else if(byteLengthSrc > 0 && byteLength >= byteLengthSrc) {
      break;
    }
    if(np == 0) {
      if((0xE0 & value[byteLength]) == 0xC0) {
        np=2-1;
      }
      else if((0xF0 & value[byteLength]) == 0xE0) {
        np=3-1;
      }
      else if((0xF8 & value[byteLength]) == 0xF0) {
        np=4-1;
      }
      length++;
    } else {
      np--;
    }
  }
  obj->byteLength = byteLength;
  obj->length = length;
  return obj;
}

CString* initCString(CString* obj, char *value) {
  initCObject((CObject *)obj, CString_NAME);
  calcLength(obj, value, -1);
  obj->value = (char*)cmemory_calloc(obj->parent.cmemory, 1, sizeof(char)*obj->byteLength+1);

  memcpy(obj->value, value, obj->byteLength);
//  obj->value[obj->byteLength] = '\0';

  return obj;
}

CString* initCStringWithLength(CString* obj, char *value, int byteLength) {
  initCObject((CObject *)obj, CString_NAME);
  calcLength(obj, value, byteLength);
  obj->value = (char*)cmemory_calloc(obj->parent.cmemory, 1, sizeof(char)*obj->byteLength+1);
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
