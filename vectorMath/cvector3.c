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

CVector3* initCVector3(CVector3* obj, CVMFloat v0, CVMFloat v1, CVMFloat v2) {
  initCObject((CObject*)obj, KVECTOR3_NAME);
  obj->value[0] = v0;
  obj->value[1] = v1;
  obj->value[2] = v2;
  return obj;
}

CVector3* createCVector3(CVMFloat v0, CVMFloat v1, CVMFloat v2) {
  return initCVector3(newCVector3(getCMemory()), v0, v1, v2);
}

CVector3* cvector3_crossProduct(CVector3* obj, CVector3* arg, CVector3* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector3(newCVector3(memory), 0.0, 0.0, 0.0);
  }
  cvector3raw_crossProduct(obj->value, arg->value, out->value);
  return out;
}

CVMFloat cvector3_dotProduct(CVector3* obj, CVector3* arg) {
  return cvector3raw_dotProduct(obj->value, arg->value);
}


CVector3* cvector3_normalize(CVector3* obj, CVector3* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector3(newCVector3(memory), 0.0, 0.0, 0.0);
  }
  cvector3raw_normalize(obj->value, out->value);
  return out;
}


CVector3* cvector3_add(CVector3* obj, CVector3* arg, CVector3* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector3(newCVector3(memory), 0.0, 0.0, 0.0);
  }
  cvector3raw_add(obj->value, arg->value, out->value);
  return out;
}

CVector3* cvector3_sub(CVector3* obj, CVector3* arg, CVector3* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector3(newCVector3(memory), 0.0, 0.0, 0.0);
  }
  cvector3raw_sub(obj->value, arg->value, out->value);
  return out;
}

void cvector3_show(CVector3* obj) {
  cvector3raw_show(obj->value);
}

CVector3* cvector3_mulScalar(CVector3* obj, CVMFloat v, CVector3* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector3(newCVector3(memory), 0.0, 0.0, 0.0);
  }
  cvector3raw_mulScalar(obj->value, v, out->value);
  return out;
}

CVector3* cvector3_divScalar(CVector3* obj, CVMFloat v, CVector3* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector3(newCVector3(memory), 0.0, 0.0, 0.0);
  }
  cvector3raw_divScalar(obj->value, v, out->value);
  return out;
}

CVMFloat cvector3_distance(CVector3* obj, CVector3* arg) {
  return cvector3raw_distance(obj->value, arg->value);
}

CVMFloat cvector3_length(CVector3* obj) {
  return cvector3raw_length(obj->value);
}
//
// Raw
//

CVector3RawRef cvector3raw_setValues(CVector3RawRef obj, CVMFloat x, CVMFloat y, CVMFloat z) {
  obj[0] = x;
  obj[1] = y;
  obj[2] = z;
  return obj;
}

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
//
// 0 1 2
// 0 1 2
CVector3RawRef cvector3raw_crossProduct(CVector3RawRef obj, CVector3RawRef arg, CVector3RawRef out) {
  CVMFloat v0 = obj[1] * arg[2] - obj[2] * arg[1];
  CVMFloat v1 = obj[2] * arg[0] - obj[0] * arg[2];
  CVMFloat v2 = obj[0] * arg[1] - obj[1] * arg[0];
  out[0] = v0;
  out[1] = v1;
  out[2] = v2;
  return out;
}


CVMFloat cvector3raw_dotProduct(CVector3RawRef obj, CVector3RawRef arg) {
  CVMFloat sum;
  sum  = obj[0] * arg[0];
  sum += obj[1] * arg[1];
  sum += obj[2] * arg[2];
  return sum;
}

CVector3RawRef cvector3raw_mulScalar(CVector3RawRef obj, CVMFloat v, CVector3RawRef out){
  out[0] = obj[0] * v;
  out[1] = obj[1] * v;
  out[2] = obj[2] * v;
  return obj;
}

CVector3RawRef cvector3raw_divScalar(CVector3RawRef obj, CVMFloat v, CVector3RawRef out) {
  CVMFloat f = 1.0/v;
  out[0] = obj[0] * f;
  out[1] = obj[1] * f;
  out[2] = obj[2] * f;
  return obj;
}

CVMFloat cvector3raw_distance(CVector3RawRef obj, CVector3RawRef v) {
  CVMFloat x = v[0]- obj[0];
  CVMFloat y = v[1]- obj[1];
  CVMFloat z = v[2]- obj[2];
  return sqrt(x*x + y*y + z*z);
}

CVMFloat cvector3raw_length(CVector3RawRef obj) {
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
