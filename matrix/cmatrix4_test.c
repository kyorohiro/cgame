#include <stdio.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix4.h"

void cmatrix4_test() {
  printf("# cmatrix4_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CMatrix4 *mat1 = cmatrix4_setValues(initCMatrix4(newCMatrix4(mem)),
     1, 2, 3, 4,
     5, 6, 7, 8,
     9, 10, 11, 12,
     13, 14, 15, 16);
   CMatrix4 *mat2 = cmatrix4_setValues(initCMatrix4(newCMatrix4(mem)),
      16, 15, 14, 13,
      12, 11, 10, 9,
      8, 7, 6, 5,
      4, 3, 2, 1);
  cmatrix4_add(mat1, mat2, mat1);

  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      if(cmatrix4_getValue(mat1, i, j) != 17) {
        printf("  NG : getValue = %f\r\n", cmatrix4_getValue(mat1, i, j));
        passed = 0;
      }
    }
  }
  releaseCObject((CObject*)mat1);
  releaseCObject((CObject*)mat2);
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
