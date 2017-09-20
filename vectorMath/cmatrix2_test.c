#include <stdio.h>
#include <math.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix2.h"
#include "cvector2.h"
#include "vectorMath/cmatrix_proj.h"

void cmatrix2_test() {
  printf("# cmatrix2_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CMatrix2 *mat1 = cmatrix2_setValues(initCMatrix2(newCMatrix2(mem)),
     1, 2,
     3, 4);
  CMatrix2 *mat2 = cmatrix2_setValues(initCMatrix2(newCMatrix2(mem)),
      4, 3,
      2, 1);

  CMatrix2 *out = cmatrix2_add(mat1, mat2, NULL);
  for(int i=0;i<2;i++) {
    for(int j=0;j<2;j++) {
      if(cmatrix2_getValue(out, i, j) != 5) {
        printf("  NG : add\r\n");
        cmatrix2_show(out);
        passed = 0;
      }
    }
  }

  cmatrix2_sub(mat1, mat2, out);
  if(cmatrix2_getValue(out, 0, 0) != -3 || cmatrix2_getValue(out, 0, 1) != -1 ||
     cmatrix2_getValue(out, 1, 0) !=1 || cmatrix2_getValue(out, 1, 1) != 3) {
       printf("  NG : sub\r\n");
       cmatrix2_show(out);
       passed = 0;
     }

  //
  // 1 2   4 3
  // 3 4   2 1
  // 1*4+2*2 1*3+2*1
  // 3*4+4*2 3*3+4*1
  // 4+4 3+2  > 8 5
  // 12+8 9+4 > 20 13
  cmatrix2_mul(mat1, mat2, out);
  if(cmatrix2_getValue(out, 0, 0) != 8 || cmatrix2_getValue(out, 0, 1) != 5 ||
     cmatrix2_getValue(out, 1, 0) != 20 || cmatrix2_getValue(out, 1, 1) != 13) {
       printf("  NG : mul\r\n");
       cmatrix2_show(out);
       passed = 0;
     }

  //
  // 1 2  1
  // 3 4  2
  // 1*1+2*2 > 5
  // 1*3+4*2 > 11
  CVector2 *vec1 = initCVector2(newCVector2(mem), 1.0, 2.0);
  CVector2 *vecO = cmatrix2_mulCVector2(mat1, vec1, NULL);
  if(vecO->value[0] != 5 || vecO->value[1] != 11) {
       printf("  NG : mulVec\r\n");
       cmatrix2_show(mat1);
       cvector2_show(vec1);
       cvector2_show(vecO);
       passed = 0;
  }

  //
  // 1 2 > 1 3
  // 3 4 > 2 4
  //
  cmatrix2_transpose(mat1, out);
  if(cmatrix2_getValue(out, 0, 0) != 1 || cmatrix2_getValue(out, 0, 1) != 3 ||
     cmatrix2_getValue(out, 1, 0) != 2 || cmatrix2_getValue(out, 1, 1) != 4) {
       printf("  NG : transpose\r\n");
       cmatrix2_show(out);
       passed = 0;
  }

  //
  // 1 2
  // 3 4 > 1*4 - 2*3 > -2
  CVMFloat v = cmatrix2_determinant(mat1);
  if(v!= -2) {
       printf("  NG : determinant %f\r\n", v);
       cmatrix2_show(out);
       passed = 0;
  }
  //         d -b   4  -2
  // -1/2 * -c  a > -3  1 / v
  //
  CVMFloat outDeterminant;
  cmatrix2_inverse(mat1, out, &outDeterminant);
  if(cmatrix2_getValue(out, 0, 0) != 4/v || cmatrix2_getValue(out, 0, 1) != -2/v ||
     cmatrix2_getValue(out, 1, 0) != -3/v || cmatrix2_getValue(out, 1, 1) != 1/v) {
       printf("  NG : transpose\r\n");
       cmatrix2_show(mat1);
       cmatrix2_show(out);
       passed = 0;
  }

  releaseCObject((CObject*)mat1);
  releaseCObject((CObject*)mat2);
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
