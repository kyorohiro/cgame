#include <stdio.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix4.h"

void cmatrix4_test() {
  printf("# cbytes_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CMatrix4 *mat = initCMatrix4(newCMatrix4(mem));

  releaseCObject((CObject*)mat);
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
