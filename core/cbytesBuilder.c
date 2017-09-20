#include<stdio.h>
#include "cbytesBuilder.h"
#include "cbytes.h"
#include "cstring.h"
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
  initCObject((CObject *)obj, CBytesBuilder_NAME);
  obj->parent.funcFree = freeCBytesBuilder;
  obj->values = initCLinkedList(newCLinkedList(obj->parent.cmemory));
  return obj;
}

CBytesBuilder* createCBytesBuilder(CBytesBuilder* obj) {
  return initCBytesBuilder(newCBytesBuilder(getCMemory()));
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

  int len = clinkedList_getLength(obj->values);
  for(int i=0;i<len;i++) {
    CBytes* tmp = (CBytes*)clinkedList_get(obj->values, i);
    memcpy((void*)(ret->value+index), (void*)tmp->value, tmp->length);
    index += tmp->length;
  }
  return ret;
}

CString* cbytesBuilder_newString(CBytesBuilder* obj) {
  CBytes *bytes = cbytesBuilder_newBytes(obj);
  CString *ret = initCStringWithLength(
    newCString(obj->parent.cmemory),
    cbytes_getBytes(bytes),
    cbytes_getLength(bytes));
  releaseCObject((CObject*)bytes);
  return ret;
}

CString* cutil_newCStringFromPath(CMemory* cmemory, char* path) {
  CBytesBuilder *builder = newCBytesBuilder(cmemory);
  builder = initCBytesBuilderFromPath(builder, path);
  CString *ret = cbytesBuilder_newString(builder);
  releaseCObject((CObject*)builder);
  return ret;
}

// util
CBytesBuilder* initCBytesBuilderFromPath(CBytesBuilder* obj, char *path) {
  CBytesBuilder *builder = initCBytesBuilder(obj);
  //
  //

  FILE *fp = fopen(path, "r");
  char buffer[1024];

  if(fp==NULL){
    printf("#1# %s", path);
    return obj;
  }

  size_t size =0;
  do {
    size = fread(buffer, 1, 1024, fp);
    if(size > 0) {
      cbytesBuilder_addChars(builder, buffer, size);
    }
  } while(size > 0);

  fclose(fp);
  return obj;
}

CBytesBuilder* createCBytesBuilderFromPath(CBytesBuilder* obj, char *path) {
  return initCBytesBuilderFromPath(newCBytesBuilder(getCMemory()), path);
}
