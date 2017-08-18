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
  cvector3raw_crossProduct(obj->value, arg->value, out->value);
  return out;
}

CMatrixValueType cvector3_dotProduct(CVector3* obj, CVector3* arg) {
  return cvector3raw_dotProduct(obj->value, arg->value);
}


CVector3* cvector3_normalize(CVector3* obj, CVector3* out) {
    cvector3raw_normalize(obj->value, out->value);
    return out;
}


CVector3* cvector3_add(CVector3* obj, CVector3* arg, CVector3* out) {
  if(out == NULL) {
    out = initCVector3(newCVector3(obj->parent.cmemory), 0.0, 0.0, 0.0);
  }
  cvector3raw_add(obj->value, arg->value, out->value);
  return out;
}

CVector3* cvector3_sub(CVector3* obj, CVector3* arg, CVector3* out) {
  if(out == NULL) {
    out = initCVector3(newCVector3(obj->parent.cmemory), 0.0, 0.0, 0.0);
  }
  cvector3raw_sub(obj->value, arg->value, out->value);
  return out;
}

void cvector3_show(CVector3* obj) {
  cvector3raw_show(obj->value);
}

CVector3* cvector3_mulScalar(CVector3* obj, CMatrixValueType v, CVector3* out) {
  if(out == NULL) {
    out = initCVector3(newCVector3(obj->parent.cmemory), 0.0, 0.0, 0.0);
  }
  cvector3raw_mulScalar(obj->value, v, out->value);
  return out;
}

CVector3* cvector3_divScalar(CVector3* obj, CMatrixValueType v, CVector3* out) {
  if(out == NULL) {
    out = initCVector3(newCVector3(obj->parent.cmemory), 0.0, 0.0, 0.0);
  }
  cvector3raw_divScalar(obj->value, v, out->value);
  return out;
}

CMatrixValueType cvector3_distance(CVector3* obj, CVector3* arg) {
  return cvector3raw_distance(obj->value, arg->value);
}

CMatrixValueType cvector3_length(CVector3* obj) {
  return cvector3raw_length(obj->value);
}
//
// Raw
//

CVector3RawRef  cvector3raw_add(CVector3RawRef obj, CVector3RawRef arg, CVector3RawRef out) {
  out[0] = obj[0] + arg[0];
  out[1] = obj[1] + arg[1];
  out[2] = obj[2] + arg[2];
  return out;
}

CVector3RawRef cvector3raw_sub(CVector3RawRef obj, CVector3RawRef arg, CVector3RawRef out){
  out[0] = obj[0] - arg[0];
  out[1] = obj[1] - arg[1];
  out[2] = obj[2] - arg[2];
  return out;
}

CVector3RawRef cvector3raw_crossProduct(CVector3RawRef obj, CVector3RawRef arg, CVector3RawRef out) {
  CMatrixValueType v0 = obj[1] * arg[2] - obj[2] * arg[1];
  CMatrixValueType v1 = obj[2] * arg[0] - obj[0] * arg[2];
  CMatrixValueType v2 = obj[0] * arg[1] - obj[1] * arg[0];
  out[0] = v0;
  out[1] = v1;
  out[2] = v2;
  return out;
}


CMatrixValueType cvector3raw_dotProduct(CVector3RawRef obj, CVector3RawRef arg) {
  CMatrixValueType sum;
  sum  = obj[0] * arg[0];
  sum += obj[1] * arg[1];
  sum += obj[2] * arg[2];
  return sum;
}

CVector3RawRef cvector3raw_mulScalar(CVector3RawRef obj, CMatrixValueType v, CVector3RawRef out){
  out[0] = obj[0] * v;
  out[1] = obj[1] * v;
  out[2] = obj[2] * v;
  return obj;
}

CVector3RawRef cvector3raw_divScalar(CVector3RawRef obj, CMatrixValueType v, CVector3RawRef out) {
  CMatrixValueType f = 1.0/v;
  out[0] = obj[0] * v;
  out[1] = obj[1] * v;
  out[2] = obj[2] * v;
  return obj;
}

CMatrixValueType cvector3raw_distance(CVector3RawRef obj, CVector3RawRef v) {
  CMatrixValueType x = v[0]- obj[0];
  CMatrixValueType y = v[1]- obj[1];
  CMatrixValueType z = v[2]- obj[2];
  return sqrt(x*x + y*y + z*z);
}

CMatrixValueType cvector3raw_length(CVector3RawRef obj) {
    double v = obj[0] * obj[0] + obj[1] * obj[1] + obj[2] * obj[2];
    return sqrt(v);
}

CVector3RawRef cvector3raw_normalize(CVector3RawRef obj, CVector3RawRef out) {
  double v = cvector3raw_length(obj);
  double f = 1.0/v;
  out[0] = obj[0]*f;
  out[1] = obj[1]*f;
  out[2] = obj[2]*f;
  return out;
}

void cvector3raw_show(CVector3RawRef obj) {
    printf("%f %f %f\n", obj[0], obj[1], obj[2]);
}
