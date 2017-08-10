#include <stdio.h>
#include "core/cmemory.h"
#include "cmatrix4.h"

extern void cmatrix4_test_add();
extern void cmatrix4_test_outer();
extern void cvector4_test_add();
extern void cvector3_test_add();
extern void cvector3_test_normalize();
extern void cvector3_test_dotProduct();
extern void cmatrix4_test_ortho();
extern void cmatrix4_test_perspective();

int test01();
int main(int argv, char** argc) {
  printf("hello world");
  cmatrix4_test_add();
  cmatrix4_test_outer();
  cvector4_test_add();
  cvector3_test_add();
  cvector3_test_normalize();
  cvector3_test_dotProduct();
  cmatrix4_test_ortho();
  cmatrix4_test_perspective();
  return 0;
}
