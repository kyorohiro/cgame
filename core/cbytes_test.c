#include <stdio.h>
#include "cbytes.h"
#include "cmemory.h"

void cbytes_test(){
  printf("# cbytes_test\n");
  CMemory *mem = initCMemory(newCMemory());
  CBytes *bye = initCBytes(newCBytes(mem), "abc", 4);
  releaseCObject((CObject*)bye);
  printf("%d == %d", mem->callocCounter, mem->freeCounter);
  freeCMemory(mem);
  printf("\r\n\r\n");
}
