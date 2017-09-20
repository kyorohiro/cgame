#include "cmatrix2.h"
#include "cvector2.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void _freeMatrix2(void* obj);

CMatrix2* newCMatrix2(CMemory* cmemory) {
  CMatrix2 *ret = (CMatrix2*)cmemory_calloc(cmemory, 1, sizeof(CMatrix2));
  ret->parent.funcFree = _freeMatrix2;
  ret->parent.cmemory = cmemory;
  return ret;
}

CMatrix2* initCMatrix2(CMatrix2* obj) {
  initCObject((CObject*)obj, KMATRIX2_NAME);
  cmatrix2_setIdentity(obj);
  return obj;
}

CMatrix2* createCMatrix2() {
  return initCMatrix2(newCMatrix2(getCMemory()));
}

void _freeMatrix2(void* tmp) {
  CMatrix2* obj = tmp;
  freeCObject(obj);
}

CMatrix2* cmatrix2_add(CMatrix2* obj, CMatrix2* arg, CMatrix2* out) {
  int i=0;
  if(out ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCMatrix2(newCMatrix2(memory));
  }
  cmatrix2raw_add(obj->value, arg->value, out->value);
  return out;
}

CMatrix2* cmatrix2_sub(CMatrix2* obj, CMatrix2* arg, CMatrix2* out) {
  int i=0;
  if(out ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCMatrix2(newCMatrix2(memory));
  }
  cmatrix2raw_sub(obj->value, arg->value, out->value);
  return out;
}

CMatrix2* cmatrix2_mul(CMatrix2* obj, CMatrix2* arg, CMatrix2* out) {
  if(out ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCMatrix2(newCMatrix2(memory));
  }

  cmatrix2raw_mul(obj->value, arg->value, out->value);

  return out;
}

CVector2* cmatrix2_mulCVector2(CMatrix2* obj, CVector2* arg, CVector2* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector2(newCVector2(memory), 0.0, 0.0);
  }
  cmatrix2raw_mulVector2Raw(obj->value, arg->value, out->value);
  return out;
}

CMatrix2* cmatrix2_setIdentity(CMatrix2* obj) {
  cmatrix2raw_setIdentity(obj->value);
  return obj;
}

CMatrix2* cmatrix2_setValues(CMatrix2* obj,
              CVMFloat a11, CVMFloat a12,
              CVMFloat a21, CVMFloat a22) {
  cmatrix2raw_setValues(obj->value,
    a11, a12,
    a21, a22);
  return obj;
}

CVMFloat cmatrix2_determinant(CMatrix2* obj) {
  return cmatrix2raw_determinant(obj->value);
}

//
//http://mathworld.wolfram.com/MatrixInverse.html
CMatrix2* cmatrix2_inverse(CMatrix2* obj, CMatrix2* outInverse, CVMFloat *outDeterminant) {
  if(outInverse ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    outInverse = initCMatrix2(newCMatrix2(memory));
  }
  cmatrix2raw_inverse(obj->value, outInverse->value, outDeterminant);
  return outInverse;
}

CMatrix2* cmatrix2_transpose(CMatrix2* obj, CMatrix2* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCMatrix2(newCMatrix2(memory));
  }
  cmatrix2raw_transpose(obj->value, out->value);
  return out;
}

CVMFloat cmatrix2_getValue(CMatrix2* obj, int row, int col) {
  return cmatrix2raw_getValue(obj->value, row, col);
}

void cmatrix2_show(CMatrix2* obj){
  cmatrix2raw_show(obj->value);
}

//
// raw
//
CMatrix2RawRef cmatrix2raw_setIdentity(CMatrix2RawRef obj) {
  obj[0] = 1.0;
  obj[2] = 0.0;

  obj[1] = 0.0;
  obj[3] = 1.0;

  return obj;
}

CMatrix2RawRef cmatrix2raw_setValues(CMatrix2RawRef obj,
              CVMFloat a11, CVMFloat a12,
              CVMFloat a21, CVMFloat a22) {
  obj[0] = a11;
  obj[2] = a12;

  obj[1] = a21;
  obj[3] = a22;

  return obj;
}

CMatrix2RawRef cmatrix2raw_copy(CMatrix2RawRef obj, CMatrix2RawRef out) {
  for(int i=0;i<4;i++) {
    out[i] = obj[i];
  }
  return out;
}

CMatrix2RawRef cmatrix2raw_add(CMatrix2RawRef obj, CMatrix2RawRef arg, CMatrix2RawRef out) {
  out[0]  = obj[0]  + arg[0];
  out[1]  = obj[1]  + arg[1];
  out[2]  = obj[2]  + arg[2];
  out[3]  = obj[3]  + arg[3];

  return out;
}

CMatrix2RawRef cmatrix2raw_sub(CMatrix2RawRef obj, CMatrix2RawRef arg, CMatrix2RawRef out) {
  out[0]  = obj[0]  - arg[0];
  out[1]  = obj[1]  - arg[1];
  out[2]  = obj[2]  - arg[2];
  out[3]  = obj[3]  - arg[3];

  return out;
}

CMatrix2RawRef cmatrix2raw_mul(CMatrix2RawRef obj, CMatrix2RawRef arg, CMatrix2RawRef out) {
  double o[4];
  for(int i=0;i<2;i++) {
    for(int j=0;j<2;j++) {
      o[i+2*j]  = obj[i+0] * arg[0+2*j];
      o[i+2*j] += obj[i+2] * arg[1+2*j];
    }
  }

  for(int k=0;k<4;k++) {
    out[k] = o[k];
  }

  return out;
}

//
// 0 1
// 2 3
CVector2RawRef cmatrix2raw_mulVector2Raw(CMatrix2RawRef obj, CVector2RawRef arg, CVector2RawRef out) {
  return cmatrix2raw_mulVector(obj, arg[0], arg[1], out);
}

CVector2RawRef cmatrix2raw_mulVector(CMatrix2RawRef obj, CVMFloat x, CVMFloat y, CVector2RawRef out) {
  CVMFloat v0 = obj[0]*x + obj[2]*y;
  CVMFloat v1 = obj[1]*x + obj[3]*y;
  out[0] = v0;
  out[1] = v1;
  return out;
}

CMatrix2RawRef cmatrix2raw_transpose(CMatrix2RawRef obj, CMatrix2RawRef out) {

  CVMFloat a11 = obj[0];
  CVMFloat a12 = obj[1];
  CVMFloat a21 = obj[2];
  CVMFloat a22 = obj[3];

  out[0] = a11;
  out[2] = a12;
  out[1] = a21;
  out[3] = a22;

  return out;
}


//
// 0 2
// 1 3
CVMFloat cmatrix2raw_determinant(CMatrix2RawRef raw) {
  return raw[0]* raw[3] - raw[2]*raw[1];
}

//
// 0 2
// 1 3
CMatrix2RawRef cmatrix2raw_inverse(CMatrix2RawRef raw, CMatrix2RawRef outInverse, CVMFloat *outDeterminant) {
  CVMFloat det = cmatrix2raw_determinant(raw);
  if(outInverse != NULL) {
    *outInverse = det;
  }
  if(det == 0) {
    outInverse[0] = 0.0;
    outInverse[2] = 0.0;
    outInverse[1] = 0.0;
    outInverse[3] = 0.0;
    return outInverse;
  }

  CVMFloat f = 1.0 / det;
  outInverse[0] = raw[3] * f;
  outInverse[2] = -1 * raw[2] * f;
  outInverse[1] = -1 * raw[1] * f;
  outInverse[3] = raw[0] * f;

  return outInverse;
}

CVMFloat cmatrix2raw_getValue(CMatrix2RawRef obj, int row, int col) {
  return obj[row+2*col];
}

void cmatrix2raw_show(CMatrix2RawRef obj) {
  for(int i=0;i<2;i++) {
    printf("%f %f \r\n",
      cmatrix2raw_getValue(obj, i, 0),
      cmatrix2raw_getValue(obj, i, 1));
  }
}
