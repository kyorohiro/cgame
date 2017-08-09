#include <stdio.h>
#include "core/cmemory.h"
#include "cmatrix4.h"

extern void cmatrix4_test_add();
extern void cmatrix4_test_outer();
extern void cvector4_test_add();
extern void cvector3_test_add();
extern void cvector3_test_normalize();
int test01();
int main(int argv, char** argc) {
  printf("hello world");
  cmatrix4_test_add();
  cmatrix4_test_outer();
  cvector4_test_add();
  cvector3_test_add();
  cvector3_test_normalize();
  return 0;
}
