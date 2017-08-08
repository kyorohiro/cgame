#include <stdio.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix4.h"
#include "cvector3.h"

void cvector3_test_add() {
  printf("# cvector3_test_add\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CVector3 *vec = initCVector3(newCVector3(mem), 1.0, 2.0, 3.0);

  if(vec->value[0] != 1.0 || vec->value[1] != 2.0 || vec->value[2] != 3.0 ) {
    printf("  NG : failed to init value \r\n");
    passed = 0;
  }


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
