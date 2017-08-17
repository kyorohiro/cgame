#include <stdio.h>
#include <math.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix4.h"
#include "cray.h"
#include "matrix/cglmatrix.h"


void cmatrix4_test_ray() {
  printf("# cmatrix4_test_ray\n");

  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CRay *mat1 = initCRay(newCRay(mem),
    0.0, 0.0, 0.0,
    0.0, 0.0, -1.0);
  releaseCObject((CObject*)mat1);
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
