#include "cmatrix4.h"
#include "cvector4.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void _freeVector4(void* tmp) {
  freeCObject(tmp);
}

CVector4* newCVector4(CMemory* cmemory) {
  CVector4 *ret = (CVector4*)cmemory_calloc(cmemory, 1, sizeof(CVector4));
  ret->parent.funcFree = _freeVector4;
  ret->parent.cmemory = cmemory;
  return ret;
}


CVector4* initCVector4(CVector4* obj, CMatrixVertexType v0, CMatrixVertexType v1, CMatrixVertexType v2, CMatrixVertexType v3) {
  initCObject((CObject*)obj, KVECTOR4_NAME);
  obj->value[0] = v0;
  obj->value[1] = v1;
  obj->value[2] = v2;
  obj->value[3] = v3;
  return obj;
}

CMatrixValueType cvector4_length(CVector4* obj) {
  return cvector4raw_length(obj->value);
}

CMatrixValueType cvector4_dotProduct(CVector4* obj, CVector4* arg) {
  return cvector4raw_dotProduct(obj->value, arg->value);
}

void cvector4_show(CVector4* obj) {
  cvector4raw_show(obj->value);
}

//
// RAW
//
CMatrixValueType cvector4raw_length(CVector4RawRef obj) {
  double v = obj[0] * obj[0] + obj[1] * obj[1] + obj[2] * obj[2] + obj[3] * obj[3];
  return sqrt(v);
}

CMatrixValueType cvector4raw_dotProduct(CVector4RawRef obj, CVector4RawRef arg) {
  CMatrixValueType sum;
  sum  = obj[0] * arg[0];
  sum += obj[1] * arg[1];
  sum += obj[2] * arg[2];
  sum += obj[3] * arg[3];
  return sum;
}

void cvector4raw_show(CVector4RawRef obj) {
  printf("%f %f %f %lf\n", obj[0], obj[1], obj[2], obj[3]);
}
