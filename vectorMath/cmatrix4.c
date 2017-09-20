#include "cmatrix4.h"
#include "cvector3.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void _freeMatrix(void* obj);

CMatrix4* newCMatrix4(CMemory* cmemory) {
  CMatrix4 *ret = (CMatrix4*)cmemory_calloc(cmemory, 1, sizeof(CMatrix4));
  ret->parent.funcFree = _freeMatrix;
  ret->parent.cmemory = cmemory;
  return ret;
}

CMatrix4* initCMatrix4(CMatrix4* obj) {
  initCObject((CObject*)obj, KMATRIX4_NAME);
  cmatrix4_setIdentity(obj);
  return obj;
}

CMatrix4* createCMatrix4() {
  return initCMatrix4(newCMatrix4(getCMemory()));
}

void _freeMatrix(void* tmp) {
  CMatrix4* obj = tmp;
  freeCObject(obj);
}

CMatrix4* cmatrix4_add(CMatrix4* obj, CMatrix4* arg, CMatrix4* out) {
  int i=0;
  if(out ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCMatrix4(newCMatrix4(memory));
  }
  cmatrix4raw_add(obj->value, arg->value, out->value);
  return out;
}

CMatrix4* cmatrix4_sub(CMatrix4* obj, CMatrix4* arg, CMatrix4* out) {
  int i=0;
  if(out ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCMatrix4(newCMatrix4(memory));
  }
  cmatrix4raw_sub(obj->value, arg->value, out->value);
  return out;
}

CMatrix4* cmatrix4_mul(CMatrix4* obj, CMatrix4* arg, CMatrix4* out) {
  if(out ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCMatrix4(newCMatrix4(memory));
  }

  cmatrix4raw_mul(obj->value, arg->value, out->value);

  return out;
}

CVector4* cmatrix4_mulCVector4(CMatrix4* obj, CVector4* arg, CVector4* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCVector4(newCVector4(memory), 0.0, 0.0, 0.0, 0.0);
  }
  cmatrix4raw_mulVector4Raw(obj->value, arg->value, out->value);
  return out;
}

CMatrix4* cmatrix4_setIdentity(CMatrix4* obj) {
  cmatrix4raw_setIdentity(obj->value);
  return obj;
}

CMatrix4* cmatrix4_setValues(CMatrix4* obj,
              CVMFloat a11, CVMFloat a12, CVMFloat a13, CVMFloat a14,
              CVMFloat a21, CVMFloat a22, CVMFloat a23, CVMFloat a24,
              CVMFloat a31, CVMFloat a32, CVMFloat a33, CVMFloat a34,
              CVMFloat a41, CVMFloat a42, CVMFloat a43, CVMFloat a44
            ) {
  cmatrix4raw_setValues(obj->value,
    a11, a12, a13, a14,
    a21, a22, a23, a24,
    a31, a32, a33, a34,
    a41, a42, a43, a44);
  return obj;
}

CVMFloat cmatrix4_determinant(CMatrix4* obj) {
  return cmatrix4raw_determinant(obj->value);
}

//
//http://mathworld.wolfram.com/MatrixInverse.html
CMatrix4* cmatrix4_inverse(CMatrix4* obj, CMatrix4* outInverse, CVMFloat *outDeterminant) {
  if(outInverse ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    outInverse = initCMatrix4(newCMatrix4(memory));
  }
  cmatrix4raw_inverse(obj->value, outInverse->value, outDeterminant);
  return outInverse;
}

CMatrix4* cmatrix4_transpose(CMatrix4* obj, CMatrix4* out) {
  if(out == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    out = initCMatrix4(newCMatrix4(memory));
  }
  cmatrix4raw_transpose(obj->value, out->value);
  return out;
}

CVMFloat cmatrix4_getValue(CMatrix4* obj, int row, int col) {
  return cmatrix4raw_getValue(obj->value, row, col);
}

void cmatrix4_show(CMatrix4* obj){
  cmatrix4raw_show(obj->value);
}

//
// raw
//
CMatrix4RawRef cmatrix4raw_setIdentity(CMatrix4RawRef obj) {
  obj[0] = 1.0;
  obj[4] = 0.0;
  obj[8] = 0.0;
  obj[12] = 0.0;

  obj[1] = 0.0;
  obj[5] = 1.0;
  obj[9] = 0.0;
  obj[13] = 0.0;

  obj[2] = 0.0;
  obj[6] = 0.0;
  obj[10] = 1.0;
  obj[14] = 0.0;

  obj[3] = 0.0;
  obj[7] = 0.0;
  obj[11] = 0.0;
  obj[15] = 1.0;
  return obj;
}

CMatrix4RawRef cmatrix4raw_setValues(CMatrix4RawRef obj,
              CVMFloat a11, CVMFloat a12, CVMFloat a13, CVMFloat a14,
              CVMFloat a21, CVMFloat a22, CVMFloat a23, CVMFloat a24,
              CVMFloat a31, CVMFloat a32, CVMFloat a33, CVMFloat a34,
              CVMFloat a41, CVMFloat a42, CVMFloat a43, CVMFloat a44) {
  obj[0] = a11;
  obj[4] = a12;
  obj[8] = a13;
  obj[12] = a14;

  obj[1] = a21;
  obj[5] = a22;
  obj[9] = a23;
  obj[13] = a24;

  obj[2] = a31;
  obj[6] = a32;
  obj[10] = a33;
  obj[14] = a34;

  obj[3] = a41;
  obj[7] = a42;
  obj[11] = a43;
  obj[15] = a44;
  return obj;
}

CMatrix4RawRef cmatrix4raw_copy(CMatrix4RawRef obj, CMatrix4RawRef out) {
  for(int i=0;i<16;i++) {
    out[i] = obj[i];
  }
  return out;
}

CMatrix4RawRef cmatrix4raw_add(CMatrix4RawRef obj, CMatrix4RawRef arg, CMatrix4RawRef out) {
  out[0]  = obj[0]  + arg[0];
  out[1]  = obj[1]  + arg[1];
  out[2]  = obj[2]  + arg[2];
  out[3]  = obj[3]  + arg[3];
  out[4]  = obj[4]  + arg[4];
  out[5]  = obj[5]  + arg[5];
  out[6]  = obj[6]  + arg[6];
  out[7]  = obj[7]  + arg[7];
  out[8]  = obj[8]  + arg[8];
  out[9]  = obj[9]  + arg[9];
  out[10] = obj[10] + arg[10];
  out[11] = obj[11] + arg[11];
  out[12] = obj[12] + arg[12];
  out[13] = obj[13] + arg[13];
  out[14] = obj[14] + arg[14];
  out[15] = obj[15] + arg[15];
  return out;
}

CMatrix4RawRef cmatrix4raw_sub(CMatrix4RawRef obj, CMatrix4RawRef arg, CMatrix4RawRef out) {
  out[0]  = obj[0]  - arg[0];
  out[1]  = obj[1]  - arg[1];
  out[2]  = obj[2]  - arg[2];
  out[3]  = obj[3]  - arg[3];
  out[4]  = obj[4]  - arg[4];
  out[5]  = obj[5]  - arg[5];
  out[6]  = obj[6]  - arg[6];
  out[7]  = obj[7]  - arg[7];
  out[8]  = obj[8]  - arg[8];
  out[9]  = obj[9]  - arg[9];
  out[10] = obj[10] - arg[10];
  out[11] = obj[11] - arg[11];
  out[12] = obj[12] - arg[12];
  out[13] = obj[13] - arg[13];
  out[14] = obj[14] - arg[14];
  out[15] = obj[15] - arg[15];
  return out;
}

CMatrix4RawRef cmatrix4raw_mul(CMatrix4RawRef obj, CMatrix4RawRef arg, CMatrix4RawRef out) {
  CVMFloat o[16];
  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      o[i+4*j]  = obj[i+0] * arg[4*j];
      o[i+4*j] += obj[i+4] * arg[1+4*j];
      o[i+4*j] += obj[i+8] * arg[2+4*j];
      o[i+4*j] += obj[i+12] * arg[3+4*j];
    }
  }

  for(int k=0;k<16;k++) {
    out[k] = o[k];
  }

  return out;
}

CVector4RawRef cmatrix4raw_mulVector4Raw(CMatrix4RawRef obj, CVector4RawRef arg, CVector4RawRef out) {
  return cmatrix4raw_mulVector(obj, arg[0], arg[1], arg[2], arg[3], out);
}

CVector4RawRef cmatrix4raw_mulVector(CMatrix4RawRef obj, CVMFloat x,  CVMFloat y, CVMFloat z, CVMFloat w, CVector4RawRef out) {
  CVMFloat v0 = obj[0]*x + obj[4]*y + obj[8]*z + obj[12]*w;
  CVMFloat v1 = obj[1]*x + obj[5]*y + obj[9]*z + obj[13]*w;
  CVMFloat v2 = obj[2]*x + obj[6]*y + obj[10]*z + obj[14]*w;
  CVMFloat v3 = obj[3]*x + obj[7]*y + obj[11]*z + obj[15]*w;
  out[0] = v0;
  out[1] = v1;
  out[2] = v2;
  out[3] = v3;
  return out;
}

CMatrix4RawRef cmatrix4raw_transpose(CMatrix4RawRef obj, CMatrix4RawRef out) {

  CVMFloat a11 = obj[0];
  CVMFloat a12 = obj[1];
  CVMFloat a13 = obj[2];
  CVMFloat a14 = obj[3];
  CVMFloat a21 = obj[4];
  CVMFloat a22 = obj[5];
  CVMFloat a23 = obj[6];
  CVMFloat a24 = obj[7];
  CVMFloat a31 = obj[8];
  CVMFloat a32 = obj[9];
  CVMFloat a33 = obj[10];
  CVMFloat a34 = obj[11];
  CVMFloat a41 = obj[12];
  CVMFloat a42 = obj[13];
  CVMFloat a43 = obj[14];
  CVMFloat a44 = obj[15];

  out[0] = a11;
  out[4] = a12;
  out[8] = a13;
  out[12] = a14;

  out[1] = a21;
  out[5] = a22;
  out[9] = a23;
  out[13] = a24;

  out[2] = a31;
  out[6] = a32;
  out[10] = a33;
  out[14] = a34;

  out[3] = a41;
  out[7] = a42;
  out[11] = a43;
  out[15] = a44;
  return out;
}


CVMFloat cmatrix4raw_determinant(CMatrix4RawRef raw) {
  double detA1 = raw[0] * raw[5] - raw[1] * raw[4];
  double detA2 = raw[0] * raw[6] - raw[2] * raw[4];
  double detA3 = raw[0] * raw[7] - raw[3] * raw[4];
  double detA12 = raw[1] * raw[6] - raw[2] * raw[5];
  double detA13 = raw[1] * raw[7] - raw[3] * raw[5];
  double detA23 = raw[2] * raw[7] - raw[3] * raw[6];

  double detB012 = raw[8] * detA12 - raw[9] * detA2 + raw[10] * detA1;
  double detB013 = raw[8] * detA13 - raw[9] * detA3 + raw[11] * detA1;
  double detB023 = raw[8] * detA23 - raw[10] * detA3 + raw[11] * detA2;
  double detB123 = raw[9] * detA23 - raw[10] * detA13 + raw[11] * detA12;


  return -detB123 * raw[12] + detB023 * raw[13] - detB013 * raw[14] + detB012 * raw[15];
}

CMatrix4RawRef cmatrix4raw_inverse(CMatrix4RawRef raw, CMatrix4RawRef outInverse, CVMFloat *outDeterminant) {
  double a00 = raw[0];
  double a01 = raw[1];
  double a02 = raw[2];
  double a03 = raw[3];
  double a10 = raw[4];
  double a11 = raw[5];
  double a12 = raw[6];
  double a13 = raw[7];
  double a20 = raw[8];
  double a21 = raw[9];
  double a22 = raw[10];
  double a23 = raw[11];
  double a30 = raw[12];
  double a31 = raw[13];
  double a32 = raw[14];
  double a33 = raw[15];
  double b00 = a00 * a11 - a01 * a10;
  double b01 = a00 * a12 - a02 * a10;
  double b02 = a00 * a13 - a03 * a10;
  double b03 = a01 * a12 - a02 * a11;
  double b04 = a01 * a13 - a03 * a11;
  double b05 = a02 * a13 - a03 * a12;
  double b06 = a20 * a31 - a21 * a30;
  double b07 = a20 * a32 - a22 * a30;
  double b08 = a20 * a33 - a23 * a30;
  double b09 = a21 * a32 - a22 * a31;
  double b10 = a21 * a33 - a23 * a31;
  double b11 = a22 * a33 - a23 * a32;
  double det = (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);
  if(outDeterminant != NULL) {
    *outDeterminant = det;
  }
  if(det == 0.0) {
    // todo throw exception
    outInverse[0] = 0.0;
    outInverse[1] = 0.0;
    outInverse[2] = 0.0;
    outInverse[3] = 0.0;
    outInverse[4] = 0.0;
    outInverse[5] = 0.0;
    outInverse[6] = 0.0;
    outInverse[7] = 0.0;
    outInverse[8] = 0.0;
    outInverse[9] = 0.0;
    outInverse[10] = 0.0;
    outInverse[11] = 0.0;
    outInverse[12] = 0.0;
    outInverse[13] = 0.0;
    outInverse[14] = 0.0;
    outInverse[15] = 0.0;
    return outInverse;
  }

  CVMFloat f = 1.0/det;
  outInverse[0] = (a11 * b11 - a12 * b10 + a13 * b09)  * f;
  outInverse[1] = (-a01 * b11 + a02 * b10 - a03 * b09) * f;
  outInverse[2] = (a31 * b05 - a32 * b04 + a33 * b03) * f;
  outInverse[3] = (-a21 * b05 + a22 * b04 - a23 * b03) * f;
  outInverse[4] = (-a10 * b11 + a12 * b08 - a13 * b07) * f;
  outInverse[5] = (a00 * b11 - a02 * b08 + a03 * b07) * f;
  outInverse[6] = (-a30 * b05 + a32 * b02 - a33 * b01) * f;
  outInverse[7] = (a20 * b05 - a22 * b02 + a23 * b01) * f;
  outInverse[8] = (a10 * b10 - a11 * b08 + a13 * b06) * f;
  outInverse[9] = (-a00 * b10 + a01 * b08 - a03 * b06) * f;
  outInverse[10] = (a30 * b04 - a31 * b02 + a33 * b00) * f;
  outInverse[11] = (-a20 * b04 + a21 * b02 - a23 * b00) * f;
  outInverse[12] = (-a10 * b09 + a11 * b07 - a12 * b06) * f;
  outInverse[13] = (a00 * b09 - a01 * b07 + a02 * b06) * f;
  outInverse[14] = (-a30 * b03 + a31 * b01 - a32 * b00) * f;
  outInverse[15] = (a20 * b03 - a21 * b01 + a22 * b00) * f;

  return outInverse;
}


CVMFloat cmatrix4raw_getValue(CMatrix4RawRef obj, int row, int col) {
  return obj[row+4*col];
}

void cmatrix4raw_show(CMatrix4RawRef obj) {
  for(int i=0;i<4;i++) {
    printf("%f %f %f %lf \r\n",
      cmatrix4raw_getValue(obj, i, 0),
      cmatrix4raw_getValue(obj, i, 1),
      cmatrix4raw_getValue(obj, i, 2),
      cmatrix4raw_getValue(obj, i, 3));
  }
}
