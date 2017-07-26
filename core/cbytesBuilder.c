#include<stdio.h>
#include "cbytesBuilder.h"


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
  return obj;
}
