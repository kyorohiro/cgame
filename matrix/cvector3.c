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

CVector3* initCVector3(CVector3* obj, CMatrixValueType v0, CMatrixValueType v1, CMatrixValueType v2) {
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
  cvector3raw_crossProduct(&obj->value, &arg->value, &out->value);
  return out;
}

CMatrixValueType cvector3_dotProduct(CVector3* obj, CVector3* arg) {
  return cvector3raw_dotProduct(&obj->value, &arg->value);
}


CMatrixValueType cvector3_normalize(CVector3* obj) {
  return cvector3raw_normalize(&obj->value);
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

//
// Raw 
//

CVector3Raw* cvector3raw_crossProduct(CVector3Raw *obj, CVector3Raw *arg, CVector3Raw *out) {
  CMatrixValueType v0 = *obj[1] * *arg[2] - *obj[2] * *arg[1];
  CMatrixValueType v1 = *obj[2] * *arg[0] - *obj[0] * *arg[2];
  CMatrixValueType v2 = *obj[0] * *arg[1] - *obj[1] * *arg[0];
  *out[0] = v0;
  *out[1] = v1;
  *out[2] = v2;
  return out;
}


CMatrixValueType cvector3raw_dotProduct(CVector3Raw* obj, CVector3Raw* arg) {
  CMatrixValueType sum;
  sum  = *obj[0] * *arg[0];
  sum += *obj[1] * *arg[1];
  sum += *obj[2] * *arg[2];
  return sum;
}

CMatrixValueType cvector3raw_normalize(CVector3Raw* obj) {
  CMatrixValueType v =
         (*obj[0] * *obj[0]) +
         (*obj[1] * *obj[1]) +
         (*obj[2] * *obj[2]);
  return sqrt(v);
}
