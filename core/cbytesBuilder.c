#include<stdio.h>
#include "cbytesBuilder.h"
#include "cbytes.h"
#include <string.h>

void freeCBytesBuilder(void* obj) {
  int i=0;
  if(obj == NULL) {
    return;
  }
  CBytesBuilder *bytesBuilderObj = (CBytesBuilder *)obj;
  releaseCObject((CObject*)bytesBuilderObj->values);
  freeCObject(obj);
}

CBytesBuilder* newCBytesBuilder(CMemory* cmemory) {
  CBytesBuilder* ret = cmemory_calloc(cmemory, 1, sizeof(CBytesBuilder));
  ret->parent.cmemory = cmemory;
  return ret;
}

CBytesBuilder* initCBytesBuilder(CBytesBuilder* obj){
  initCObject((CObject *)obj, CBYTESBUILDER_NAME);
  obj->parent.funcFree = freeCBytesBuilder;
  obj->values = initCLinkedList(newCLinkedList(obj->parent.cmemory));
  return obj;
}

CBytesBuilder* cbytesBuilder_addChars(CBytesBuilder* obj, char* v, int length) {
  clinkedList_addLast(
    obj->values,
    cobject_downCounter(
      (CObject*)initCBytes(
      newCBytes(obj->parent.cmemory),
      v, length))
    );
    obj->length += length;
  return obj;
}

int cbytesBuilder_getLength(CBytesBuilder* obj) {
  return obj->length;
}

CBytes* cbytesBuilder_newBytes(CBytesBuilder* obj) {
  int length = obj->length;
  CBytes *ret = initCBytes(newCBytes(obj->parent.cmemory), NULL, length);
  int index = 0;
  for(int i=0;i<length;i++) {
    CBytes* tmp = (CBytes*)clinkedList_get(obj->values, i);
    memcpy((void*)(ret->value+index), (void*)tmp->value, tmp->length);
    index += tmp->length;
  }
  return ret;
}