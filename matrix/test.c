#include <stdio.h>
#include "core/cmemory.h"
#include "cmatrix4.h"

extern void cmatrix4_test_add();
extern void cmatrix4_test_multiply();
extern void cvector4_test_add();
extern void cvector3_test_add();
extern void cvector3_test_normalize();
extern void cvector3_test_dotProduct();
extern void cvector2_test_add();
extern void cmatrix4_test_ortho();
extern void cmatrix4_test_perspective();
extern void cmatrix4_test_lookAt();
extern void cmatrix4_test_inverse();
extern void cmatrix4_test_ray();

int test01();
int main(int argv, char** argc) {
  printf("hello world");
  cmatrix4_test_add();
  cmatrix4_test_multiply();
  cvector2_test_add();
  cvector3_test_add();
  cvector3_test_normalize();
  cvector3_test_dotProduct();
  cmatrix4_test_ortho();
  cmatrix4_test_perspective();
  cmatrix4_test_lookAt();
  cmatrix4_test_inverse();
  cmatrix4_test_ray();
  cvector4_test_add();
  return 0;
}
