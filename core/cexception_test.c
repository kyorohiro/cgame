#include <stdio.h>
#include "cexception.h"
#include "cmemory.h"

void cexception_test(){
  printf("# cexception_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CException *exe = initCException(newCException(mem));


  releaseCObject((CObject*)exe);
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
