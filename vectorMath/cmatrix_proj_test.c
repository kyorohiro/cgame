#include <stdio.h>
#include <math.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix4.h"
#include "vectorMath/cmatrix_proj.h"
#include "vectorMath/cvector3.h"


void cmatrix4_test_ortho() {
  printf("# cmatrix4_test_ortho\n");

  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  // CMatrix4 *obj, double right, double left,
  //double top, double bottom,
  //double far, double near)Values(
  CMatrix4 *mat1 = cmatrix4_setOrthogonalProjection( initCMatrix4(newCMatrix4(mem)),
     1.0, -1.0, 1.0, -1.0,
     0.1, 1000.0);
  if(
    cmatrix4_getValue(mat1,0,0) != 1.0 ||
    cmatrix4_getValue(mat1,0,1) != 0.0 ||
    cmatrix4_getValue(mat1,0,2) != 0.0 ||
    cmatrix4_getValue(mat1,0,3) != -0.0 ||

    cmatrix4_getValue(mat1,1,0) != 0.0 ||
    cmatrix4_getValue(mat1,1,1) != 1.0 ||
    cmatrix4_getValue(mat1,1,2) != 0.0 ||
    cmatrix4_getValue(mat1,1,3) != -0.0 ||

    cmatrix4_getValue(mat1,2,0) != 0.0 ||
    cmatrix4_getValue(mat1,2,1) != 0.0 ||
    floor(cmatrix4_getValue(mat1,2,2)*10000) != 20 ||
    floor(cmatrix4_getValue(mat1,2,3)*10000) != 10002 ||

    cmatrix4_getValue(mat1,3,0) != 0.0 ||
    cmatrix4_getValue(mat1,3,1) != 0.0 ||
    cmatrix4_getValue(mat1,3,2) != 0.0 ||
    cmatrix4_getValue(mat1,3,3) != 1.0

) {
  printf("# NG :\n");
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



void cmatrix4_test_perspective() {
  printf("# cmatrix4_test_perspective\n");

  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  double fov = 3.1415 / 2;
  double aspectRatio = 2.0;
  double zNear = 1.0;
  double zFar = 100.0;
/*
  double fov = 3.1415 * 90.0 / 180.0;
  double aspectRatio = 1.77777;
  double zNear = 1.0;
  double zFar = 1000.0;*/

  CMatrix4 *mat1 = cmatrix4_setPerspectiveProjection(initCMatrix4(newCMatrix4(mem)),
     fov, aspectRatio,
     zFar, zNear);

  if(
    floor(cmatrix4_getValue(mat1,0,0)*1000) != 500 ||
    floor(cmatrix4_getValue(mat1,0,1)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,0,2)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,0,3)*1000) != 0 ||

    floor(cmatrix4_getValue(mat1,1,0)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,1,1)*1000) != 1000 ||
    floor(cmatrix4_getValue(mat1,1,2)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,1,3)*1000) != 0 ||

    floor(cmatrix4_getValue(mat1,2,0)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,2,1)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,2,2)*1000) != -1021 ||
    floor(cmatrix4_getValue(mat1,2,3)*1000) != -2021 ||

    floor(cmatrix4_getValue(mat1,3,0)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,3,1)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,3,2)*1000) != -1000 ||
    floor(cmatrix4_getValue(mat1,3,3)*1000) != 0

) {
  printf("# NG %f:\n", floor(cmatrix4_getValue(mat1,2,3)*1000));
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



void cmatrix4_test_lookAt() {
  printf("# cmatrix4_test_lookAt\n");

  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());

  CMatrix4 *mat1 = cmatrix4_setLookAt(
    initCMatrix4(newCMatrix4(mem)),
    0.0, 0.0, 0.0,
    0.0, 0.0, -1.0,
    0.0, 1.0,0.0);

  if(
    floor(cmatrix4_getValue(mat1,0,0)*1000) != 1000 ||
    floor(cmatrix4_getValue(mat1,0,1)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,0,2)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,0,3)*1000) != 0 ||

    floor(cmatrix4_getValue(mat1,1,0)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,1,1)*1000) != 1000 ||
    floor(cmatrix4_getValue(mat1,1,2)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,1,3)*1000) != 0 ||

    floor(cmatrix4_getValue(mat1,2,0)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,2,1)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,2,2)*1000) != 1000 ||
    floor(cmatrix4_getValue(mat1,2,3)*1000) != 0 ||

    floor(cmatrix4_getValue(mat1,3,0)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,3,1)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,3,2)*1000) != 0 ||
    floor(cmatrix4_getValue(mat1,3,3)*1000) != 1000

) {
  printf("# NG %f:\n", floor(cmatrix4_getValue(mat1,2,3)*1000));
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

//

void cmatrix4_test_unproject() {
  printf("# cmatrix4_test_unproject\n");
  CVector3* position = initCVector3(newCVector3(getCMemory()), 0.0, 0.0, 0.0);
  CVector3* focusPosition = initCVector3(newCVector3(getCMemory()), 0.0, 0.0, -1.0);
  CVector3* upDirection = initCVector3(newCVector3(getCMemory()), 0.0, 1.0, 0.0);
  CMatrix4* lookat = initCMatrix4(newCMatrix4(getCMemory()));
  cmatrix4_setLookAt(lookat,
    0.0, 0.0, 0.0,
    0.0, 0.0, -1.0,
    0.0, 1.0, 0.0);

  double n = 0.1;
  double f = 1000.0;
  double l = -10.0;
  double r = 10.0;
  double b = -10.0;
  double t = 10.0;

  CMatrix4* frustum = initCMatrix4(newCMatrix4(getCMemory()));
  cmatrix4_setFrustumProjection(frustum, l, r, b, t, n, f);
  CMatrix4* C = cmatrix4_mul(frustum, lookat, NULL);
  CVector3* re =  initCVector3(newCVector3(getCMemory()), 0.0, 0.0, 0.0);
  CVector3* out = initCVector3(newCVector3(getCMemory()), 0.0, 0.0, 0.0);
  int ret = cmatrix4_unproject(
      C,
      0.0, 100.0, 0.0, 100.0, 50.0, 50.0, 1.0,
      out);
      printf(">>%d\r\n", ret);
  cvector3_show(out);
}
