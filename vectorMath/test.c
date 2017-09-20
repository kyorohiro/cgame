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

extern void cmatrix2_test();
extern void cmatrix3_test();
extern void cmatrix4_test();
//
extern void cmatrix4_test_ray();
extern void cmatrix4_test_ray2();
//
extern void cmatrix4_test_ortho();
extern void cmatrix4_test_perspective();
extern void cmatrix4_test_lookAt();
extern void cmatrix4_test_inverse();
extern void cmatrix4_test_unproject();
int test01();
int main(int argv, char** argc) {
  printf("hello world");
  cmatrix4_test_add();
  cmatrix4_test_multiply();



  cvector2_test_add();
  cvector3_test_add();
  cvector3_test_normalize();
  cvector3_test_dotProduct();
  cvector4_test_add();

  cmatrix2_test();
  cmatrix3_test();
  cmatrix4_test();

  cmatrix4_test_ray();
  cmatrix4_test_ray2();
  //
  cmatrix4_test_ortho();
  cmatrix4_test_perspective();
  cmatrix4_test_lookAt();
  cmatrix4_test_inverse();
  //
  cmatrix4_test_unproject();

  return 0;
}
