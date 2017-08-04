#include "cmatrix4.h"
#include <stdlib.h>
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
//CMatrix4* setRotateX(CMatrix4* obj, double angle) {
//
//}
//
CMatrix4* cmatrix4_setIdentity(CMatrix4* obj) {
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
CMatrix4* cmatrix4_setRotationY(CMatrix4* obj, double radians){
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
CMatrix4* cmatrix4_setRotationX(CMatrix4* obj, double radians){
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
CMatrix4* cmatrix4_setRotationZ(CMatrix4* obj, double radians){
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

CMatrix4* cmatrix4_setTranslation(CMatrix4* obj, double x, double y, double z) {
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

CMatrix4* cmatrix4_setScale(CMatrix4* obj, double x, double y, double z) {
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
