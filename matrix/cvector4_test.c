#include <stdio.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix4.h"
#include "cvector4.h"

void cvector4_test_add() {
  printf("# cvector4_test_add\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CVector4 *vec = initCVector4(newCVector4(mem),0.0,0.0,0.0);
  releaseCObject((CObject*)vec);
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
