#include "object.h"
#include "cmemory.h"
#include <stdio.h>
#include <stdlib.h>

void __free(void *ptr) {
  free(ptr);
}

void* __calloc(int num, int size) {
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
