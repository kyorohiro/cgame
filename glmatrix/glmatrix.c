#include "glmatrix.h"
#include <stdlib.h>

void _freeMatrix(void* obj);

KMatrix* newMatrix() {
  KMatrix *ret = (KMatrix*)calloc(1, sizeof(KMatrix));
  ret->parent.funcFree = _freeMatrix;
  return ret;
}

KMatrix* initMatrix(KMatrix* obj) {
  return obj;
}

void _freeMatrix(void* tmp) {
  KMatrix* obj = tmp;
  freeCObject(obj);
}

KMatrix* add(KMatrix* obj, KMatrix* arg, KMatrix* out) {
  int i=0;
  if(out ==NULL) {
    out = initMatrix(newMatrix());
  }
  for(i=0;i<16;i++) {
    out->value[i] = obj->value[i] + arg->value[i];
  }
  return out;
}

KMatrix* sub(KMatrix* obj, KMatrix* arg, KMatrix* out) {
  int i=0;
  if(out ==NULL) {
    out = initMatrix(newMatrix());
  }
  for(i=0;i<16;i++) {
    out->value[i] = obj->value[i] - arg->value[i];
  }
  return out;
}

KMatrix* outer(KMatrix* obj, KMatrix* arg, KMatrix* out) {
  if(out ==NULL) {
    out = initMatrix(newMatrix());
  }
  int i=0;
  int j=0;
  for(j=0;j<4;j++){
    for(i=0;i<4;i++) {
        out->value[4*j+i] = obj->value[j] * arg->value[i];
    }
  }
  return out;
}

//
//KMatrix* setRotateX(KMatrix* obj, double angle) {
//
//}
//
KMatrix* setIdentity(KMatrix* obj) {
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
