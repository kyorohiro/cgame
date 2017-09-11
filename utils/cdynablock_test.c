#include <stdio.h>
#include "utils/cdynablock.h"

int main(int argc, char** argv) {
  printf("Hello, World!!");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CDynaBlock *objBlock = initCDynaBlock(newCDynaBlock(mem), 100, 100);
  releaseCObject((CObject*)objBlock);

  if(mem->callocCounter != mem->freeCounter) {
    printf("  NG : %d == %d\r\n", mem->callocCounter, mem->freeCounter);
    passed = 0;
  }


  freeCMemory(mem);
  if(passed) {
    printf("  OK : \r\n");
  }
  return 0;
}
