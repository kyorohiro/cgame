#include <stdio.h>
#include <math.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix4.h"
#include "vectorMath/cmatrix_proj.h"


void cmatrix4_test() {
  printf("# cmatrix4_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CMatrix4 *mat1 = cmatrix4_setValues(initCMatrix4(newCMatrix4(mem)),
     1,  2,   3,  4,
     5,  6,   7,  8,
     9,  10, 11, 12,
    13, 14, 15, 16);
  CMatrix4 *mat2 = cmatrix4_setValues(initCMatrix4(newCMatrix4(mem)),
    16, 15, 14, 13,
    12, 11, 10,  9,
     8,  7,  6,  5,
     4,  3,  2,  1);
  CMatrix4 *mat3 = cmatrix4_setValues(initCMatrix4(newCMatrix4(mem)),
     1,  2,  3,  4,
     2,  3,  4,  3,
     3,  4,  3,  2,
     4,  3,  2,  1);
  CMatrix4 *out = cmatrix4_add(mat1, mat2, NULL);
  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      if(cmatrix4_getValue(out, i, j) != 17) {
        printf("  NG : add\r\n");
        cmatrix4_show(out);
        passed = 0;
        break;
      }
    }
  }

  cmatrix4_mul(mat1, mat2, out);
  if(cmatrix4_getValue(out, 0, 0) != 80 || cmatrix4_getValue(out, 0, 1) != 70 ||
             cmatrix4_getValue(out, 0, 2) != 60 || cmatrix4_getValue(out, 0, 3) != 50 ||
     cmatrix4_getValue(out, 1, 0) !=240   || cmatrix4_getValue(out, 1, 1) != 214  ||
             cmatrix4_getValue(out, 1, 2) != 188  || cmatrix4_getValue(out, 1, 3) != 162 ||
     cmatrix4_getValue(out, 2, 0) !=400    || cmatrix4_getValue(out, 2, 1) != 358   ||
             cmatrix4_getValue(out, 2, 2) != 316   || cmatrix4_getValue(out, 2, 3) != 274  ||
     cmatrix4_getValue(out, 3, 0) !=560    || cmatrix4_getValue(out, 3, 1) != 502 ||
             cmatrix4_getValue(out, 3, 2) != 444  || cmatrix4_getValue(out, 3, 3) != 386
   ) {
       printf("  NG : sub\r\n");
       cmatrix4_show(out);
       passed = 0;
  }




  //
  // 1 2 3  1
  // 4 5 6  2
  // 7 8 9  3
  //
  // 1*1+2*2+3*3 > 1+4+9    > 14
  // 4*1+5*2+6*3 > 4+10+18  > 32
  // 7*1+8*2+9*3 > 7+16+27  > 50
  CVector4 *vec1 = initCVector4(newCVector4(mem), 1.0, 2.0, 3.0, 4.0);
  CVector4 *vecO = cmatrix4_mulCVector4(mat1, vec1, NULL);
  if(vecO->value[0] != 30 || vecO->value[1] != 70 || vecO->value[2] != 110 || vecO->value[3] != 150) {
       printf("  NG : mulVec\r\n");
       cmatrix4_show(mat1);
       cvector4_show(vec1);
       cvector4_show(vecO);
       passed = 0;
  }

  cmatrix4_transpose(mat1, out);
  if(cmatrix4_getValue(out, 0, 0) != 1 || cmatrix4_getValue(out, 0, 1) != 5 ||
             cmatrix4_getValue(out, 0, 2) != 9 || cmatrix4_getValue(out, 0, 3) != 13 ||
     cmatrix4_getValue(out, 1, 0) != 2   || cmatrix4_getValue(out, 1, 1) != 6  ||
             cmatrix4_getValue(out, 1, 2) != 10  || cmatrix4_getValue(out, 1, 3) != 14 ||
     cmatrix4_getValue(out, 2, 0) != 3    || cmatrix4_getValue(out, 2, 1) != 7   ||
             cmatrix4_getValue(out, 2, 2) != 11   || cmatrix4_getValue(out, 2, 3) != 15  ||
     cmatrix4_getValue(out, 3, 0) != 4    || cmatrix4_getValue(out, 3, 1) != 8 ||
             cmatrix4_getValue(out, 3, 2) != 12  || cmatrix4_getValue(out, 3, 3) != 16
   ) {
       printf("  NG : sub\r\n");
       cmatrix4_show(out);
       passed = 0;
  }

  //
  CVMFloat v = cmatrix4_determinant(mat1);
  if(v!= 0) {
       printf("  NG : determinant %f\r\n", v);
       cmatrix4_show(out);
       passed = 0;
  }

  CVMFloat outDeterminant;
  cmatrix4_inverse(mat3, out, &outDeterminant);
  if((int)(cmatrix4_getValue(out, 0, 0)*10) != 1 || (int)(cmatrix4_getValue(out, 0, 1)*10) != 0 ||
             (int)(cmatrix4_getValue(out, 0, 2)*10) != -5 || (int)(cmatrix4_getValue(out, 0, 3)*10) != 6 ||
     (int)(cmatrix4_getValue(out, 1, 0)*10) != 0   || (int)(cmatrix4_getValue(out, 1, 1)*10)  != -5  ||
             (int)(cmatrix4_getValue(out, 1, 2)*10) != 10  || (int)(cmatrix4_getValue(out, 1, 3)*10) != -5 ||
     (int)(cmatrix4_getValue(out, 2, 0)*10) != -5    || (int)(cmatrix4_getValue(out, 2, 1)*10) != 10  ||
             (int)(cmatrix4_getValue(out, 2, 2)*10) != -5   || (int)(cmatrix4_getValue(out, 2, 3)*10) != 0 ||
     (int)(cmatrix4_getValue(out, 3, 0)*10) != 6    || (int)(cmatrix4_getValue(out, 3, 1)*10) != -5 ||
             (int)(cmatrix4_getValue(out, 3, 2)*10) != 0  || (int)(cmatrix4_getValue(out, 3, 3)*10) != 1
   ) {
       printf("  NG : sub\r\n");
       cmatrix4_show(out);
       passed = 0;
  }

  releaseCObject((CObject*)mat1);
  releaseCObject((CObject*)mat2);
  releaseCObject((CObject*)mat3);
  releaseCObject((CObject*)out);
  releaseCObject((CObject*)vec1);
  releaseCObject((CObject*)vecO);
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
  CVMFloat out;
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
    (int)(cmatrix4_getValue(mat1,0,3)*100) != 47 ||

    (int)(cmatrix4_getValue(mat1,1,0)*1000) != 125 ||
    (int)(cmatrix4_getValue(mat1,1,1)*1000) != -625 ||
    (int)(cmatrix4_getValue(mat1,1,2)*1000) != 875 ||
    (int)(cmatrix4_getValue(mat1,1,3)*1000) != -375 ||

    (int)(cmatrix4_getValue(mat1,2,0)*1000) != -375 ||
    (int)(cmatrix4_getValue(mat1,2,1)*1000) != 875 ||
    (int)(cmatrix4_getValue(mat1,2,2)*1000) != -625 ||
    (int)(cmatrix4_getValue(mat1,2,3)*1000) != 125 ||

    (int)(cmatrix4_getValue(mat1,3,0)*100) != 47 ||
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
