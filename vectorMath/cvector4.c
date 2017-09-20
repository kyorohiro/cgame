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


CVector4* initCVector4(CVector4* obj, CVMFloat v0, CVMFloat v1, CVMFloat v2, CVMFloat v3) {
  initCObject((CObject*)obj, KVECTOR4_NAME);
  obj->value[0] = v0;
  obj->value[1] = v1;
  obj->value[2] = v2;
  obj->value[3] = v3;
  return obj;
}

CVector4* createCVector4(CVMFloat v0, CVMFloat v1, CVMFloat v2, CVMFloat v3) {
  return initCVector4(newCVector4(getCMemory()), v0, v1, v2, v3);
}

CVMFloat cvector4_length(CVector4* obj) {
  return cvector4raw_length(obj->value);
}

CVector4* cvector4_normalize(CVector4* obj, CVector4* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector4(newCVector4(memory), 0.0, 0.0, 0.0, 0.0);
  }
  cvector4raw_normalize(obj->value, out->value);
  return out;
}

CVector4* cvector4_add(CVector4* obj, CVector4* arg, CVector4* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector4(newCVector4(memory), 0.0, 0.0, 0.0, 0.0);
  }
  cvector4raw_add(obj->value, arg->value, out->value);
  return out;
}

CVector4* cvector4_sub(CVector4* obj, CVector4* arg, CVector4* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector4(newCVector4(memory), 0.0, 0.0, 0.0, 0.0);
  }
  cvector4raw_sub(obj->value, arg->value, out->value);
  return out;
}

CVector4* cvector4_mulScalar(CVector4* obj, CVMFloat v, CVector4* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector4(newCVector4(memory), 0.0, 0.0, 0.0, 0.0);
  }
  cvector4raw_mulScalar(obj->value, v, out->value);
  return out;
}

CVector4* cvector4_divScalar(CVector4* obj, CVMFloat v, CVector4* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector4(newCVector4(memory), 0.0, 0.0, 0.0, 0.0);
  }
  cvector4raw_divScalar(obj->value, v, out->value);
  return out;
}


CVMFloat cvector4_distance(CVector4* obj, CVector4* arg) {
  return cvector4raw_distance(obj->value, arg->value);
}

CVMFloat cvector4_dotProduct(CVector4* obj, CVector4* arg) {
  return cvector4raw_dotProduct(obj->value, arg->value);
}


void cvector4_show(CVector4* obj) {
  cvector4raw_show(obj->value);
}

//
// RAW
//

CVector4RawRef cvector4raw_setValues(CVector4RawRef obj, CVMFloat x, CVMFloat y, CVMFloat z, CVMFloat w) {
  obj[0] = x;
  obj[1] = y;
  obj[2] = z;
  obj[3] = w;
  return obj;
}

CVector4RawRef cvector4raw_add(CVector4RawRef obj, CVector4RawRef arg, CVector4RawRef out) {
  out[0] = obj[0] + arg[0];
  out[1] = obj[1] + arg[1];
  out[2] = obj[2] + arg[2];
  out[3] = obj[3] + arg[3];
  return out;
}

CVector4RawRef cvector4raw_sub(CVector4RawRef obj, CVector4RawRef arg, CVector4RawRef out) {
  out[0] = obj[0] - arg[0];
  out[1] = obj[1] - arg[1];
  out[2] = obj[2] - arg[2];
  out[3] = obj[3] - arg[3];
  return out;
}

CVector4RawRef cvector4raw_mulScalar(CVector4RawRef obj, CVMFloat v, CVector4RawRef out) {
  out[0] = obj[0] * v;
  out[1] = obj[1] * v;
  out[2] = obj[2] * v;
  out[3] = obj[3] * v;
  return obj;
}

CVector4RawRef cvector4raw_divScalar(CVector4RawRef obj, CVMFloat v, CVector4RawRef out) {
  CVMFloat f = 1.0/v;
  out[0] = obj[0] * f;
  out[1] = obj[1] * f;
  out[2] = obj[2] * f;
  out[3] = obj[3] * f;
  return obj;
}

CVMFloat cvector4raw_length(CVector4RawRef obj) {
  double v = obj[0] * obj[0] + obj[1] * obj[1] + obj[2] * obj[2] + obj[3] * obj[3];
  return sqrt(v);
}


CVector4RawRef cvector4raw_normalize(CVector4RawRef obj, CVector4RawRef out) {
  double v = cvector4raw_length(obj);
  double f = 1.0/v;
  out[0] = obj[0]*f;
  out[1] = obj[1]*f;
  out[2] = obj[2]*f;
  out[3] = obj[3]*f;
  return out;
}

CVMFloat cvector4raw_distance(CVector4RawRef obj, CVector4RawRef v) {
  CVMFloat x = v[0]- obj[0];
  CVMFloat y = v[1]- obj[1];
  CVMFloat z = v[2]- obj[2];
  CVMFloat w = v[3]- obj[3];
  return sqrt(x*x + y*y + z*z + w*w);
}

CVMFloat cvector4raw_dotProduct(CVector4RawRef obj, CVector4RawRef arg) {
  CVMFloat sum;
  sum  = obj[0] * arg[0];
  sum += obj[1] * arg[1];
  sum += obj[2] * arg[2];
  sum += obj[3] * arg[3];
  return sum;
}

void cvector4raw_show(CVector4RawRef obj) {
  printf("%f %f %f %lf\n", obj[0], obj[1], obj[2], obj[3]);
}
