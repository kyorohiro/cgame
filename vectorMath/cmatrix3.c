#include "cmatrix3.h"
#include "cvector3.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void _freeMatrix3(void* obj);

CMatrix3* newCMatrix3(CMemory* cmemory) {
  CMatrix3 *ret = (CMatrix3*)cmemory_calloc(cmemory, 1, sizeof(CMatrix3));
  ret->parent.funcFree = _freeMatrix3;
  ret->parent.cmemory = cmemory;
  return ret;
}

CMatrix3* initCMatrix3(CMatrix3* obj) {
  initCObject((CObject*)obj, KMATRIX3_NAME);
  cmatrix3_setIdentity(obj);
  return obj;
}

CMatrix3* createCMatrix3() {
  return initCMatrix3(newCMatrix3(getCMemory()));
}

void _freeMatrix3(void* tmp) {
  CMatrix3* obj = tmp;
  freeCObject(obj);
}

CMatrix3* cmatrix3_add(CMatrix3* obj, CMatrix3* arg, CMatrix3* out) {
  int i=0;
  if(out ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCMatrix3(newCMatrix3(memory));
  }
  cmatrix3raw_add(obj->value, arg->value, out->value);
  return out;
}

CMatrix3* cmatrix3_sub(CMatrix3* obj, CMatrix3* arg, CMatrix3* out) {
  int i=0;
  if(out ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCMatrix3(newCMatrix3(memory));
  }
  cmatrix3raw_sub(obj->value, arg->value, out->value);
  return out;
}

CMatrix3* cmatrix3_mul(CMatrix3* obj, CMatrix3* arg, CMatrix3* out) {
  if(out ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCMatrix3(newCMatrix3(memory));
  }

  cmatrix3raw_mul(obj->value, arg->value, out->value);

  return out;
}

CVector3* cmatrix3_mulCVector3(CMatrix3* obj, CVector3* arg, CVector3* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector3(newCVector3(memory), 0.0, 0.0, 0.0);
  }
  cmatrix3raw_mulVector3Raw(obj->value, arg->value, out->value);
  return out;
}

CMatrix3* cmatrix3_setIdentity(CMatrix3* obj) {
  cmatrix3raw_setIdentity(obj->value);
  return obj;
}

CMatrix3* cmatrix3_setValues(CMatrix3* obj,
              CVMFloat a11, CVMFloat a12, CVMFloat a13,
              CVMFloat a21, CVMFloat a22, CVMFloat a23,
              CVMFloat a31, CVMFloat a32, CVMFloat a33
            ) {
  cmatrix3raw_setValues(obj->value,
    a11, a12, a13,
    a21, a22, a23,
    a31, a32, a33);
  return obj;
}

CVMFloat cmatrix3_determinant(CMatrix3* obj) {
  return cmatrix3raw_determinant(obj->value);
}

//
//http://mathworld.wolfram.com/MatrixInverse.html
CMatrix3* cmatrix3_inverse(CMatrix3* obj, CMatrix3* outInverse, CVMFloat *outDeterminant) {
  if(outInverse ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    outInverse = initCMatrix3(newCMatrix3(memory));
  }
  cmatrix3raw_inverse(obj->value, outInverse->value, outDeterminant);
  return outInverse;
}

CMatrix3* cmatrix3_transpose(CMatrix3* obj, CMatrix3* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCMatrix3(newCMatrix3(memory));
  }
  cmatrix3raw_transpose(obj->value, out->value);
  return out;
}

CVMFloat cmatrix3_getValue(CMatrix3* obj, int row, int col) {
  return cmatrix3raw_getValue(obj->value, row, col);
}

void cmatrix3_show(CMatrix3* obj){
  cmatrix3raw_show(obj->value);
}

//
// raw
//
CMatrix3RawRef cmatrix3raw_setIdentity(CMatrix3RawRef obj) {
  obj[0] = 1.0;
  obj[3] = 0.0;
  obj[6] = 0.0;

  obj[1] = 0.0;
  obj[4] = 1.0;
  obj[7] = 0.0;

  obj[2] = 0.0;
  obj[5] = 0.0;
  obj[8] = 1.0;
  return obj;
}

CMatrix3RawRef cmatrix3raw_setValues(CMatrix3RawRef obj,
              CVMFloat a11, CVMFloat a12, CVMFloat a13,
              CVMFloat a21, CVMFloat a22, CVMFloat a23,
              CVMFloat a31, CVMFloat a32, CVMFloat a33) {
  obj[0] = a11;
  obj[3] = a12;
  obj[6] = a13;

  obj[1] = a21;
  obj[4] = a22;
  obj[7] = a23;

  obj[2] = a31;
  obj[5] = a32;
  obj[8] = a33;

  return obj;
}

CMatrix3RawRef cmatrix3raw_copy(CMatrix3RawRef obj, CMatrix3RawRef out) {
  for(int i=0;i<9;i++) {
    out[i] = obj[i];
  }
  return out;
}

CMatrix3RawRef cmatrix3raw_add(CMatrix3RawRef obj, CMatrix3RawRef arg, CMatrix3RawRef out) {
  out[0]  = obj[0]  + arg[0];
  out[1]  = obj[1]  + arg[1];
  out[2]  = obj[2]  + arg[2];
  out[3]  = obj[3]  + arg[3];
  out[4]  = obj[4]  + arg[4];
  out[5]  = obj[5]  + arg[5];
  out[6]  = obj[6]  + arg[6];
  out[7]  = obj[7]  + arg[7];
  out[8]  = obj[8]  + arg[8];
  return out;
}

CMatrix3RawRef cmatrix3raw_sub(CMatrix3RawRef obj, CMatrix3RawRef arg, CMatrix3RawRef out) {
  out[0]  = obj[0]  - arg[0];
  out[1]  = obj[1]  - arg[1];
  out[2]  = obj[2]  - arg[2];
  out[3]  = obj[3]  - arg[3];
  out[4]  = obj[4]  - arg[4];
  out[5]  = obj[5]  - arg[5];
  out[6]  = obj[6]  - arg[6];
  out[7]  = obj[7]  - arg[7];
  out[8]  = obj[8]  - arg[8];

  return out;
}

CMatrix3RawRef cmatrix3raw_mul(CMatrix3RawRef obj, CMatrix3RawRef arg, CMatrix3RawRef out) {
  double o[9];
  for(int i=0;i<3;i++) {
    for(int j=0;j<3;j++) {
      o[i+3*j]  = obj[i+0] * arg[0+3*j];
      o[i+3*j] += obj[i+3] * arg[1+3*j];
      o[i+3*j] += obj[i+6] * arg[2+3*j];
    }
  }

  for(int k=0;k<9;k++) {
    out[k] = o[k];
  }

  return out;
}

CVector3RawRef cmatrix3raw_mulVector3Raw(CMatrix3RawRef obj, CVector3RawRef arg, CVector3RawRef out) {
  return cmatrix3raw_mulVector(obj, arg[0], arg[1], arg[2], out);
}

CVector3RawRef cmatrix3raw_mulVector(CMatrix3RawRef obj, CVMFloat x, CVMFloat y, CVMFloat z, CVector3RawRef out) {
  CVMFloat v0 = obj[0]*x + obj[3]*y + obj[6]*z;
  CVMFloat v1 = obj[1]*x + obj[4]*y + obj[7]*z;
  CVMFloat v2 = obj[2]*x + obj[5]*y + obj[8]*z;
  out[0] = v0;
  out[1] = v1;
  out[2] = v2;
  return out;

}

CMatrix3RawRef cmatrix3raw_transpose(CMatrix3RawRef obj, CMatrix3RawRef out) {

  CVMFloat a11 = obj[0];
  CVMFloat a12 = obj[1];
  CVMFloat a13 = obj[2];
  CVMFloat a21 = obj[3];
  CVMFloat a22 = obj[4];
  CVMFloat a23 = obj[5];
  CVMFloat a31 = obj[6];
  CVMFloat a32 = obj[7];
  CVMFloat a33 = obj[8];

  out[0] = a11;
  out[3] = a12;
  out[6] = a13;

  out[1] = a21;
  out[4] = a22;
  out[7] = a23;

  out[2] = a31;
  out[5] = a32;
  out[8] = a33;

  return out;
}


//
// 0 3 6
// 1 4 7
// 2 5 8
CVMFloat cmatrix3raw_determinant(CMatrix3RawRef raw) {
  CVMFloat a0 = raw[0] *(raw[4] * raw[8] - raw[5] * raw[7]);
  CVMFloat a1 = raw[1] *(raw[3] * raw[8] - raw[5] * raw[6]);
  CVMFloat a2 = raw[2] *(raw[3] * raw[7] - raw[4] * raw[6]);

  return a0 - a1 + a2;
}

// 0 3 6
// 1 4 7
// 2 5 8
CMatrix3RawRef cmatrix3raw_inverse(CMatrix3RawRef raw, CMatrix3RawRef outInverse, CVMFloat *outDeterminant) {
  CVMFloat det = cmatrix3raw_determinant(raw);
  if(outInverse != NULL) {
    *outInverse = det;
  }
  if(det == 0) {
    outInverse[0] = 0.0;
    outInverse[1] = 0.0;
    outInverse[2] = 0.0;
    outInverse[3] = 0.0;
    outInverse[4] = 0.0;
    outInverse[5] = 0.0;
    outInverse[6] = 0.0;
    outInverse[7] = 0.0;
    outInverse[8] = 0.0;
    return outInverse;
  }
  CVMFloat f = 1.0/det;
  CVMFloat i0 =(raw[4] * raw[8] - raw[5] * raw[7]);
  CVMFloat i3 =-1*(raw[1] * raw[8] - raw[7] * raw[2]);
  CVMFloat i6 =(raw[1] * raw[5] - raw[4] * raw[2]);
  CVMFloat i1 =-1*(raw[3] * raw[8] - raw[6] * raw[5]);
  CVMFloat i4 =(raw[0] * raw[8] - raw[2] * raw[6]);
  CVMFloat i7 =-1*(raw[0] * raw[5] - raw[3] * raw[2]);
  CVMFloat i2 =(raw[3] * raw[7] - raw[6] * raw[4]);
  CVMFloat i5 =-1*(raw[0] * raw[7] - raw[6] * raw[1]);
  CVMFloat i8 =(raw[0] * raw[4] - raw[3] * raw[1]);

  outInverse[0] = i0 * f;
  outInverse[1] = i3 * f;
  outInverse[2] = i6 * f;
  outInverse[3] = i1 * f;
  outInverse[4] = i4 * f;
  outInverse[5] = i7 * f;
  outInverse[6] = i2 * f;
  outInverse[7] = i5 * f;
  outInverse[8] = i8 * f;

  return outInverse;
}

CVMFloat cmatrix3raw_getValue(CMatrix3RawRef obj, int row, int col) {
  return obj[row+3*col];
}

void cmatrix3raw_show(CMatrix3RawRef obj) {
  for(int i=0;i<3;i++) {
    printf("%f %f %f \r\n",
      cmatrix3raw_getValue(obj, i, 0),
      cmatrix3raw_getValue(obj, i, 1),
      cmatrix3raw_getValue(obj, i, 2));
  }
}
