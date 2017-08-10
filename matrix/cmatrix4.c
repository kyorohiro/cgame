#include "cmatrix4.h"
#include "cvector3.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void _freeMatrix(void* obj);

CMatrix4* newCMatrix4(CMemory* cmemory) {
  CMatrix4 *ret = (CMatrix4*)cmemory_calloc(cmemory, 1, sizeof(CMatrix4));
  ret->parent.funcFree = _freeMatrix;
  ret->parent.cmemory = cmemory;
  return ret;
}

CMatrix4* initCMatrix4(CMatrix4* obj) {
  initCObject((CObject*)obj, KMATRIX_NAME);
  return obj;
}

void _freeMatrix(void* tmp) {
  CMatrix4* obj = tmp;
  freeCObject(obj);
}

CMatrix4* cmatrix4_add(CMatrix4* obj, CMatrix4* arg, CMatrix4* out) {
  int i=0;
  if(out ==NULL) {
    out = initCMatrix4(newCMatrix4(obj->parent.cmemory));
  }
  for(i=0;i<16;i++) {
    out->value[i] = obj->value[i] + arg->value[i];
  }
  return out;
}

CMatrix4* cmatrix4_sub(CMatrix4* obj, CMatrix4* arg, CMatrix4* out) {
  int i=0;
  if(out ==NULL) {
    out = initCMatrix4(newCMatrix4(obj->parent.cmemory));
  }
  for(i=0;i<16;i++) {
    out->value[i] = obj->value[i] - arg->value[i];
  }
  return out;
}

CMatrix4* cmatrix4_outer(CMatrix4* obj, CMatrix4* arg, CMatrix4* out) {
  if(out ==NULL) {
    out = initCMatrix4(newCMatrix4(obj->parent.cmemory));
  }
  int i=0;
  int j=0;
  double o[16];
  for(i=0;i<4;i++) {
    for(j=0;j<4;j++) {
      o[i+4*j]  = obj->value[i+0] * arg->value[4*j];
      o[i+4*j] += obj->value[i+4] * arg->value[1+4*j];
      o[i+4*j] += obj->value[i+8] * arg->value[2+4*j];
      o[i+4*j] += obj->value[i+12] * arg->value[3+4*j];
//      printf("%f %f %f %f \r\n", obj->value[4*i+0], obj->value[4*i+1], obj->value[4*i+2],  obj->value[4*i+3]);
    }
  }

  for(i=0;i<16;i++) {
    out->value[i] = o[i];
  }
  return out;
}

//
//CMatrix4* setRotateX(CMatrix4* obj, double angle) {
//
//}
//
CMatrix4* cmatrix4_setIdentity(CMatrix4* obj) {
  obj->value[0] = 1.0;
  obj->value[4] = 0.0;
  obj->value[8] = 0.0;
  obj->value[12] = 0.0;

  obj->value[1] = 0.0;
  obj->value[5] = 1.0;
  obj->value[9] = 0.0;
  obj->value[13] = 0.0;

  obj->value[2] = 0.0;
  obj->value[6] = 0.0;
  obj->value[10] = 1.0;
  obj->value[13] = 0.0;

  obj->value[3] = 0.0;
  obj->value[7] = 0.0;
  obj->value[11] = 0.0;
  obj->value[15] = 1.0;

  return obj;
}

//     col 0 1 2 3
// row
//   0    a11 a12 a13 a14
//   1    a21 a22 a23 a24
//   2
//   3
CMatrix4* cmatrix4_setValues(CMatrix4* obj,
              CMatrixValue a11, CMatrixValue a12, CMatrixValue a13, CMatrixValue a14,
              CMatrixValue a21, CMatrixValue a22, CMatrixValue a23, CMatrixValue a24,
              CMatrixValue a31, CMatrixValue a32, CMatrixValue a33, CMatrixValue a34,
              CMatrixValue a41, CMatrixValue a42, CMatrixValue a43, CMatrixValue a44
            ) {
  obj->value[0] = a11;
  obj->value[4] = a12;
  obj->value[8] = a13;
  obj->value[12] = a14;

  obj->value[1] = a21;
  obj->value[5] = a22;
  obj->value[9] = a23;
  obj->value[13] = a24;

  obj->value[2] = a31;
  obj->value[6] = a32;
  obj->value[10] = a33;
  obj->value[14] = a34;

  obj->value[3] = a41;
  obj->value[7] = a42;
  obj->value[11] = a43;
  obj->value[15] = a44;

  return obj;
}


//     col 0 1 2 3
// row
//   0
//   1
//   2
//   3
CMatrixValue cmatrix4_getValue(CMatrix4* obj, int row, int col) {
  return obj->value[row+4*col];
}

void cmatrix4_show(CMatrix4* obj){
  for(int i=0;i<4;i++) {
    printf("%f %f %f %lf \r\n",
      cmatrix4_getValue(obj, i, 0),
      cmatrix4_getValue(obj, i, 1),
      cmatrix4_getValue(obj, i, 2),
      cmatrix4_getValue(obj, i, 3));
  }
}
