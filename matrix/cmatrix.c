#include "cmatrix.h"
#include <stdlib.h>
#include <math.h>

void _freeMatrix(void* obj);

CMatrix* newCMatrix() {
  CMatrix *ret = (CMatrix*)calloc(1, sizeof(CMatrix));
  ret->parent.funcFree = _freeMatrix;
  return ret;
}

CMatrix* initCMatrix(CMatrix* obj) {
  initCObject((CObject*)obj, KMATRIX_NAME);
  return obj;
}

void _freeMatrix(void* tmp) {
  CMatrix* obj = tmp;
  freeCObject(obj);
}

CMatrix* cmatrix_add(CMatrix* obj, CMatrix* arg, CMatrix* out) {
  int i=0;
  if(out ==NULL) {
    out = initCMatrix(newCMatrix());
  }
  for(i=0;i<16;i++) {
    out->value[i] = obj->value[i] + arg->value[i];
  }
  return out;
}

CMatrix* cmatrix_sub(CMatrix* obj, CMatrix* arg, CMatrix* out) {
  int i=0;
  if(out ==NULL) {
    out = initCMatrix(newCMatrix());
  }
  for(i=0;i<16;i++) {
    out->value[i] = obj->value[i] - arg->value[i];
  }
  return out;
}

CMatrix* cmatrix_outer(CMatrix* obj, CMatrix* arg, CMatrix* out) {
  if(out ==NULL) {
    out = initCMatrix(newCMatrix());
  }
  int i=0;
  int j=0;
  double o[16];
  for(i=0;i<4;i++) {
    for(j=0;j<4;j++) {
      o[4*i+j] = arg->value[4*i]*arg->value[4+j];
      o[4*i+j] += arg->value[4*i+1]*arg->value[8+j];
      o[4*i+j] += arg->value[4*i+2]*arg->value[12+j];
      o[4*i+j] += arg->value[4*i*3]*arg->value[16+j];
    }
  }

  for(i=0;i<16;i++) {
    out->value[i] = o[i];
  }
  return out;
}

//
//CMatrix* setRotateX(CMatrix* obj, double angle) {
//
//}
//
CMatrix* cmatrix_setIdentity(CMatrix* obj) {
  obj->value[0] = 1.0;
  obj->value[1] = 0.0;
  obj->value[2] = 0.0;
  obj->value[3] = 0.0;

  obj->value[4] = 0.0;
  obj->value[5] = 1.0;
  obj->value[6] = 0.0;
  obj->value[7] = 0.0;

  obj->value[8] = 0.0;
  obj->value[9] = 0.0;
  obj->value[10] = 1.0;
  obj->value[11] = 0.0;

  obj->value[12] = 0.0;
  obj->value[13] = 0.0;
  obj->value[14] = 0.0;
  obj->value[15] = 1.0;

  return obj;
}

// c 0 s
// 0 1 0
//-s 0 c
CMatrix* cmatrix_setRotationY(CMatrix* obj, double radians){
  double c = cos(radians);
  double s = sin(radians);
  obj->value[0] = c;
  obj->value[1] = 0.0;
  obj->value[2] = s;
  obj->value[3] = 0.0;

  obj->value[4] = 0.0;
  obj->value[5] = 1.0;
  obj->value[6] = 0.0;
  obj->value[7] = 0.0;

  obj->value[8] = -s;
  obj->value[9] = 0.0;
  obj->value[10] = c;
  obj->value[11] = 0.0;

  obj->value[12] = 0.0;
  obj->value[13] = 0.0;
  obj->value[14] = 0.0;
  obj->value[15] = 1.0;
  return obj;
}

// 1 0 0
// 0 c -s
// 0 s c
CMatrix* cmatrix_setRotationX(CMatrix* obj, double radians){
  double c = cos(radians);
  double s = sin(radians);
  obj->value[0] = 1;
  obj->value[1] = 0.0;
  obj->value[2] = 0.0;
  obj->value[3] = 0.0;

  obj->value[4] = 0.0;
  obj->value[5] = c;
  obj->value[6] = -s;
  obj->value[7] = 0.0;

  obj->value[8] = 0.0;
  obj->value[9] = s;
  obj->value[10] = c;
  obj->value[11] = 0.0;

  obj->value[12] = 0.0;
  obj->value[13] = 0.0;
  obj->value[14] = 0.0;
  obj->value[15] = 1.0;
  return obj;
}

// 1 0 0
// 0 c -s
// 0 s c
CMatrix* cmatrix_setRotationZ(CMatrix* obj, double radians){
  double c = cos(radians);
  double s = sin(radians);
  obj->value[0] = c;
  obj->value[1] = -s;
  obj->value[2] = 0.0;
  obj->value[3] = 0.0;

  obj->value[4] = s;
  obj->value[5] = c;
  obj->value[6] = 0.0;
  obj->value[7] = 0.0;

  obj->value[8] = 0.0;
  obj->value[9] = 0.0;
  obj->value[10] = 1.0;
  obj->value[11] = 0.0;

  obj->value[12] = 0.0;
  obj->value[13] = 0.0;
  obj->value[14] = 0.0;
  obj->value[15] = 1.0;
  return obj;
}

CMatrix* cmatrix_setTranslation(CMatrix* obj, double x, double y, double z) {
  obj->value[0] = 1.0;
  obj->value[1] = 0.0;
  obj->value[2] = 0.0;
  obj->value[3] = x;

  obj->value[4] = 0.0;
  obj->value[5] = 1.0;
  obj->value[6] = 0.0;
  obj->value[7] = y;

  obj->value[8] = 0.0;
  obj->value[9] = 0.0;
  obj->value[10] = 1.0;
  obj->value[11] = z;

  obj->value[12] = 0.0;
  obj->value[13] = 0.0;
  obj->value[14] = 0.0;
  obj->value[15] = 1.0;
  return obj;
}

CMatrix* cmatrix_setScale(CMatrix* obj, double x, double y, double z) {
  obj->value[0] = x;
  obj->value[1] = 0.0;
  obj->value[2] = 0.0;
  obj->value[3] = 0.0;

  obj->value[4] = y;
  obj->value[5] = 1.0;
  obj->value[6] = 0.0;
  obj->value[7] = 0.0;

  obj->value[8] = 0.0;
  obj->value[9] = 0.0;
  obj->value[10] = z;
  obj->value[11] = 0.0;

  obj->value[12] = 0.0;
  obj->value[13] = 0.0;
  obj->value[14] = 0.0;
  obj->value[15] = 1.0;
  return obj;
}
