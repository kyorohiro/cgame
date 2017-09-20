#include "cmatrix4.h"
#include "cvector2.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void _freeVector2(void* tmp) {
  freeCObject(tmp);
}

CVector2* newCVector2(CMemory* cmemory) {
  CVector2 *ret = (CVector2*)cmemory_calloc(cmemory, 1, sizeof(CVector2));
  ret->parent.funcFree = _freeVector2;
  ret->parent.cmemory = cmemory;
  return ret;
}

CVector2* initCVector2(CVector2* obj, CVMFloat v0, CVMFloat v1) {
  initCObject((CObject*)obj, KVECTOR2_NAME);
  obj->value[0] = v0;
  obj->value[1] = v1;
  return obj;
}

CVector2* createCVector2(CVMFloat v0, CVMFloat v1) {
  return initCVector2(newCVector2(getCMemory()), v0, v1);
}

CVMFloat cvector2_crossProduct(CVector2* obj, CVector2* arg) {
  return cvector2raw_crossProduct(obj->value, arg->value);
}

CVMFloat cvector2_dotProduct(CVector2* obj, CVector2* arg) {
  return cvector2raw_dotProduct(obj->value, arg->value);
}


CVector2* cvector2_normalize(CVector2* obj, CVector2* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector2(newCVector2(memory), 0.0, 0.0);
  }
  cvector2raw_normalize(obj->value, out->value);
  return out;
}


CVector2* cvector2_add(CVector2* obj, CVector2* arg, CVector2* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector2(newCVector2(memory), 0.0, 0.0);
  }
  cvector2raw_add(obj->value, arg->value, out->value);
  return out;
}

CVector2* cvector2_sub(CVector2* obj, CVector2* arg, CVector2* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector2(newCVector2(memory), 0.0, 0.0);
  }
  cvector2raw_sub(obj->value, arg->value, out->value);
  return out;
}

void cvector2_show(CVector2* obj) {
  cvector2raw_show(obj->value);
}

CVector2* cvector2_mulScalar(CVector2* obj, CVMFloat v, CVector2* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector2(newCVector2(memory), 0.0, 0.0);
  }
  cvector2raw_mulScalar(obj->value, v, out->value);
  return out;
}

CVector2* cvector2_divScalar(CVector2* obj, CVMFloat v, CVector2* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector2(newCVector2(memory), 0.0, 0.0);
  }
  cvector2raw_divScalar(obj->value, v, out->value);
  return out;
}

CVMFloat cvector2_distance(CVector2* obj, CVector2* arg) {
  return cvector2raw_distance(obj->value, arg->value);
}

CVMFloat cvector2_length(CVector2* obj) {
  return cvector2raw_length(obj->value);
}
//
// Raw
//

CVector2RawRef  cvector2raw_add(CVector2RawRef obj, CVector2RawRef arg, CVector2RawRef out) {
  out[0] = obj[0] + arg[0];
  out[1] = obj[1] + arg[1];
  return out;
}

CVector2RawRef cvector2raw_sub(CVector2RawRef obj, CVector2RawRef arg, CVector2RawRef out){
  out[0] = obj[0] - arg[0];
  out[1] = obj[1] - arg[1];
  return out;
}

CVMFloat cvector2raw_crossProduct(CVector2RawRef obj, CVector2RawRef arg) {
  return (obj[0] * arg[1] - obj[1] * arg[0]);
}


CVMFloat cvector2raw_dotProduct(CVector2RawRef obj, CVector2RawRef arg) {
  CVMFloat sum;
  sum  = obj[0] * arg[0];
  sum += obj[1] * arg[1];
  return sum;
}

CVector2RawRef cvector2raw_mulScalar(CVector2RawRef obj, CVMFloat v, CVector2RawRef out){
  out[0] = obj[0] * v;
  out[1] = obj[1] * v;
  return obj;
}

CVector2RawRef cvector2raw_divScalar(CVector2RawRef obj, CVMFloat v, CVector2RawRef out) {
  CVMFloat f = 1.0/v;
  out[0] = obj[0] * f;
  out[1] = obj[1] * f;
  return obj;
}

CVMFloat cvector2raw_distance(CVector2RawRef obj, CVector2RawRef v) {
  CVMFloat x = v[0]- obj[0];
  CVMFloat y = v[1]- obj[1];
  return sqrt(x*x + y*y);
}

CVMFloat cvector2raw_length(CVector2RawRef obj) {
    double v = obj[0] * obj[0] + obj[1] * obj[1];
    return sqrt(v);
}

CVector2RawRef cvector2raw_normalize(CVector2RawRef obj, CVector2RawRef out) {
  double v = cvector2raw_length(obj);
  double f = 1.0/v;
  out[0] = obj[0]*f;
  out[1] = obj[1]*f;
  return out;
}

void cvector2raw_show(CVector2RawRef obj) {
    printf("%f %f\n", obj[0], obj[1]);
}
