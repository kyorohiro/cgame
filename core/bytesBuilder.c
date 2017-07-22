#include "bytesBuilder.h"

void freeBytesBuilder(void* obj) {
  int i=0;
  if(obj == NULL) {
    return;
  }
  BytesBuilder *bytesBuilderObj = (BytesBuilder *)obj;
  releaseCObject(bytesBuilderObj->values);
  freeCObject(obj);
}

BytesBuilder* newBytesBuilder(CMemory* cmemory) {
  BytesBuilder* ret = cmemory_calloc(cmemory, 1, sizeof(BytesBuilder));
  ret->parent.cmemory = cmemory;
  return ret;
}

BytesBuilder* initBytesBuilder(BytesBuilder* obj){
  initCObject((CObject *)obj, BYTESBUILDER_NAME);
  obj->parent.funcFree = freeBytesBuilder;
  obj->values = initLinkedList(newLinkedList(obj->parent.cmemory));
  return obj;
}
