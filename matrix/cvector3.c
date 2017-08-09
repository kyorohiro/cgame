#include "cmatrix4.h"
#include "cvector3.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void _freeVector3(void* tmp) {
  freeCObject(tmp);
}

CVector3* newCVector3(CMemory* cmemory) {
  CVector3 *ret = (CVector3*)cmemory_calloc(cmemory, 1, sizeof(CVector3));
  ret->parent.funcFree = _freeVector3;
  ret->parent.cmemory = cmemory;
  return ret;
}

CVector3* initCVector3(CVector3* obj, CMatrixValue v0, CMatrixValue v1, CMatrixValue v2) {
  initCObject((CObject*)obj, KVECTOR3_NAME);
  obj->value[0] = v0;
  obj->value[1] = v1;
  obj->value[2] = v2;
  return obj;
}

CVector3* cvector3_crossProduct(CVector3* obj, CVector3* arg, CVector3* out) {
  if(out == NULL) {
    out = initCVector3(newCVector3(obj->parent.cmemory), 0.0, 0.0, 0.0);
  }
  CMatrixValue v0 = obj->value[1] * arg->value[2] - obj->value[2] * arg->value[1];
  CMatrixValue v1 = obj->value[2] * arg->value[0] - obj->value[0] * arg->value[2];
  CMatrixValue v2 = obj->value[0] * arg->value[1] - obj->value[1] * arg->value[0];
  out->value[0] = v0;
  out->value[1] = v1;
  out->value[2] = v2;
  return out;
}

CMatrixValue cvector3_dotProduct(CVector3* obj, CVector3* arg) {
  double sum;
  sum  = obj->value[0] * arg->value[0];
  sum += obj->value[1] * arg->value[1];
  sum += obj->value[2] * arg->value[2];
  return sum;
}

CMatrixValue cvector3_normalize(CVector3* obj) {
  double v =
         (obj->value[0]*obj->value[0]) +
         (obj->value[1]*obj->value[1]) +
         (obj->value[2]*obj->value[2]);
  return sqrt(v);
}

CVector3* cvector3_add(CVector3* obj, CVector3* arg, CVector3* out) {
  if(out == NULL) {
    out = initCVector3(newCVector3(obj->parent.cmemory), 0.0, 0.0, 0.0);
  }
  out->value[0] = obj->value[0] + arg->value[0];
  out->value[1] = obj->value[1] + arg->value[1];
  out->value[2] = obj->value[2] + arg->value[2];
  return out;
}

CVector3* cvector3_sub(CVector3* obj, CVector3* arg, CVector3* out) {
  if(out == NULL) {
    out = initCVector3(newCVector3(obj->parent.cmemory), 0.0, 0.0, 0.0);
  }
  out->value[0] = obj->value[0] - arg->value[0];
  out->value[1] = obj->value[1] - arg->value[1];
  out->value[2] = obj->value[2] - arg->value[2];
  return out;
}
