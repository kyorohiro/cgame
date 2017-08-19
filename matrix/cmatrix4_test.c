#include <stdio.h>
#include <math.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix4.h"
#include "matrix/cglmatrix.h"

void cmatrix4_test_add() {
  printf("# cmatrix4_test_add\n");
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
  //
  //
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

void cmatrix4_test_multiply() {
  printf("# cmatrix4_test_outer\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CMatrix4 *mat1 = cmatrix4_setValues(initCMatrix4(newCMatrix4(mem)),
     1, 5, 9, 13,
     2, 6, 10, 14,
     3, 7, 11, 15,
     4, 8, 12, 16);
  CMatrix4 *mat2 = cmatrix4_setValues(initCMatrix4(newCMatrix4(mem)),
      16, 12, 8, 4,
      15, 11, 7, 3,
      14, 10, 6, 2,
      13, 9, 5, 1);
  CMatrix4 *mat3 = cmatrix4_setValues(initCMatrix4(newCMatrix4(mem)),
      386, 274, 162, 50,
      444, 316, 188, 60,
      502, 358, 214, 70,
      560, 400, 240, 80);
  mat1 = cmatrix4_mul(mat1, mat2, mat1);
  cmatrix4_show(mat1);

  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      if(cmatrix4_getValue(mat1, i, j) != cmatrix4_getValue(mat3, i, j)) {
        printf("  NG : getValue(%d,%d) =%f\r\n", i, j, cmatrix4_getValue(mat1, i, j));
        passed = 0;
      }
    }
  }
  releaseCObject((CObject*)mat1);
  releaseCObject((CObject*)mat2);
  releaseCObject((CObject*)mat3);
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

void cmatrix4_test_inverse() {
  printf("# cmatrix4_test_inverse\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CMatrixValueType out;
  CMatrix4 *mat1 = cmatrix4_setValues(initCMatrix4(newCMatrix4(mem)),
     1, 2, 3, 4,
     2, 4, 5, 3,
     3, 5, 4, 2,
     4, 3, 2, 1);
  cmatrix4_inverse(mat1, mat1, &out);

  if(
    (int)(cmatrix4_getValue(mat1,0,0)*1000) != -25 ||
    (int)(cmatrix4_getValue(mat1,0,1)*1000) != 125 ||
    (int)(cmatrix4_getValue(mat1,0,2)*1000) != -375 ||
    (int)(cmatrix4_getValue(mat1,0,3)*1000) != 474 ||

    (int)(cmatrix4_getValue(mat1,1,0)*1000) != 125 ||
    (int)(cmatrix4_getValue(mat1,1,1)*1000) != -625 ||
    (int)(cmatrix4_getValue(mat1,1,2)*1000) != 875 ||
    (int)(cmatrix4_getValue(mat1,1,3)*1000) != -375 ||

    (int)(cmatrix4_getValue(mat1,2,0)*1000) != -375 ||
    (int)(cmatrix4_getValue(mat1,2,1)*1000) != 875 ||
    (int)(cmatrix4_getValue(mat1,2,2)*1000) != -625 ||
    (int)(cmatrix4_getValue(mat1,2,3)*1000) != 125 ||

    (int)(cmatrix4_getValue(mat1,3,0)*1000) != 474 ||
    (int)(cmatrix4_getValue(mat1,3,1)*1000) != -375 ||
    (int)(cmatrix4_getValue(mat1,3,2)*1000) != 125 ||
    (int)(cmatrix4_getValue(mat1,3,3)*1000) != -25
) {
  printf("# NG %d:\n", (int)(cmatrix4_getValue(mat1,0,3)*1000) );
  cmatrix4_show(mat1);
  passed = 0;
  }

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
