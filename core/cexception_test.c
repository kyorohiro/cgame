#include <stdio.h>
#include "cexception.h"
#include "cmemory.h"

void _testtest() {
  cexception_throw(getCException(), NULL);
}

void cexception_test(){
  printf("# cexception_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CException *exe = initCException(newCException(mem));


  CTry {
    printf("test try\r\n");
    _testtest();
  } CCatch {
    printf("test catch\r\n");
  }
    printf("test end\r\n");

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
