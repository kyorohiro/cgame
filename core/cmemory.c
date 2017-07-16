#include "object.h"
#include "cmemory.h"
#include <stdio.h>
#include <stdlib.h>

void __free(void* obj,void *ptr) {
  ((CMemory*)obj)->freeCounter++;
  free(ptr);
}

void* __calloc(void* obj,int num, int size) {
  ((CMemory*)obj)->callocCounter++;
  return calloc(num, size);
}

CMemory* newCMemory() {
  return malloc(sizeof(CMemory));
}

CMemory* initCMemory(CMemory* obj) {
  obj->calloc = __calloc;
  obj->free = __free;
  return obj;
}

void freeCMemory(CMemory* obj) {
  free(obj);
}

void* cmemory_calloc(CMemory* obj, int num, int size) {
  return obj->calloc(obj,num,size);
}

void cmemory_free(CMemory* obj, void *ptr) {
  obj->free(obj,ptr);
}

CMemory* defaultCMemory = NULL;
CMemory* getCMemory() {
    if(defaultCMemory == NULL) {
        defaultCMemory = initCMemory(newCMemory());
    }
    return defaultCMemory;
}
