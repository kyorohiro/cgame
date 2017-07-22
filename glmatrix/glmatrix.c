#include "glmatrix.h"
#include <stdlib.h>
#include <math.h>

void _freeMatrix(void* obj);

KMatrix* newKMatrix() {
  KMatrix *ret = (KMatrix*)calloc(1, sizeof(KMatrix));
  ret->parent.funcFree = _freeMatrix;
  return ret;
}

KMatrix* initKMatrix(KMatrix* obj) {
  initCObject((CObject*)obj, KMATRIX_NAME);
  return obj;
}

void _freeMatrix(void* tmp) {
  KMatrix* obj = tmp;
  freeCObject(obj);
}

KMatrix* kmatrix_add(KMatrix* obj, KMatrix* arg, KMatrix* out) {
  int i=0;
  if(out ==NULL) {
    out = initKMatrix(newKMatrix());
  }
  for(i=0;i<16;i++) {
    out->value[i] = obj->value[i] + arg->value[i];
  }
  return out;
}

KMatrix* kmatrix_sub(KMatrix* obj, KMatrix* arg, KMatrix* out) {
  int i=0;
  if(out ==NULL) {
    out = initKMatrix(newKMatrix());
  }
  for(i=0;i<16;i++) {
    out->value[i] = obj->value[i] - arg->value[i];
  }
  return out;
}

KMatrix* kmatrix_outer(KMatrix* obj, KMatrix* arg, KMatrix* out) {
  if(out ==NULL) {
    out = initKMatrix(newKMatrix());
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
//KMatrix* setRotateX(KMatrix* obj, double angle) {
//
//}
//
KMatrix* kmatrix_setIdentity(KMatrix* obj) {
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
KMatrix* kmatrix_setRotationY(KMatrix* obj, double radians){
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
KMatrix* kmatrix_setRotationX(KMatrix* obj, double radians){
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
KMatrix* kmatrix_setRotationZ(KMatrix* obj, double radians){
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

KMatrix* kmatrix_setTranslation(KMatrix* obj, double x, double y, double z) {
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

KMatrix* kmatrix_setScale(KMatrix* obj, double x, double y, double z) {
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
