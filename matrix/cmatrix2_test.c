#include <stdio.h>
#include <math.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix2.h"
#include "matrix/cglmatrix.h"

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
  //
  releaseCObject((CObject*)mat1);
  releaseCObject((CObject*)mat2);
  releaseCObject((CObject*)out);

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
