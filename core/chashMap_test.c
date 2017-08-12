#include <stdio.h>
#include <string.h>
#include "cmemory.h"
#include "chashMap.h"


void chashMap_test(){
  printf("# chashMap_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CHashMap *map = initCHashMap(newCHashMap(mem));


  releaseCObject((CObject*)map);
  if(mem->callocCounter != mem->freeCounter) {
    printf("  NG : %d == %d\r\n", mem->callocCounter, mem->freeCounter);
    passed = 0;
  }

  freeCMemory(mem);
  if(passed) {
    printf("  OK : \r\n");
  }
  printf("\r\n\r\n");
}
