#include "bytesBuilder.h"

BytesBuilder* newBytesBuilder(CMemory* cmemory) {
  BytesBuilder* ret = cmemory_calloc(cmemory, 1, sizeof(BytesBuilder));
  ret->parent.cmemory = cmemory;
  return ret;
}
BytesBuilder* initBytesBuilder(BytesBuilder* obj){
  initCObject((CObject *)obj, BYTESBUILDER_NAME);
  return obj;
}
