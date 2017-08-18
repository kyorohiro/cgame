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
  initCObject((CObject*)obj, KMATRIX_NAME);
  return obj;
}

void _freeMatrix(void* tmp) {
  CMatrix4* obj = tmp;
  freeCObject(obj);
}

CMatrix4* cmatrix4_add(CMatrix4* obj, CMatrix4* arg, CMatrix4* out) {
  int i=0;
  if(out ==NULL) {
    out = initCMatrix4(newCMatrix4(obj->parent.cmemory));
  }
  cmatrix4raw_add(obj->value, arg->value, out->value);
  return out;
}

CMatrix4* cmatrix4_sub(CMatrix4* obj, CMatrix4* arg, CMatrix4* out) {
  int i=0;
  if(out ==NULL) {
    out = initCMatrix4(newCMatrix4(obj->parent.cmemory));
  }
  cmatrix4raw_sub(obj->value, arg->value, out->value);
  return out;
}

CMatrix4* cmatrix4_multiply(CMatrix4* obj, CMatrix4* arg, CMatrix4* out) {
  if(out ==NULL) {
    out = initCMatrix4(newCMatrix4(obj->parent.cmemory));
  }

  cmatrix4raw_mul(obj->value, arg->value, out->value);

  return out;
}

CVector4* cmatrix4_multiplyCVector4(CMatrix4* obj, CVector4* arg, CVector4* out) {
  if(out == NULL) {
    out = initCVector4(newCVector4(obj->parent.cmemory), 0.0, 0.0, 0.0, 0.0);
  }
  CMatrixVertexType v0 = obj->value[0]*arg->value[0] +
                    obj->value[4]*arg->value[1] +
                    obj->value[8]*arg->value[2] +
                    obj->value[12]*arg->value[3];
  CMatrixVertexType v1 = obj->value[1]*arg->value[0] +
                    obj->value[5]*arg->value[1] +
                    obj->value[9]*arg->value[2] +
                    obj->value[13]*arg->value[3];
  CMatrixVertexType v2 = obj->value[2]*arg->value[0] +
                    obj->value[6]*arg->value[1] +
                    obj->value[10]*arg->value[2] +
                    obj->value[14]*arg->value[3];
  CMatrixVertexType v3 = obj->value[3]*arg->value[0] +
                    obj->value[7]*arg->value[1] +
                    obj->value[11]*arg->value[2] +
                    obj->value[15]*arg->value[3];
  out->value[0] = v0;
  out->value[1] = v1;
  out->value[2] = v2;
  out->value[3] = v3;
  return out;
}
//
//CMatrix4* setRotateX(CMatrix4* obj, double angle) {
//
//}
//
CMatrix4* cmatrix4_setIdentity(CMatrix4* obj) {
  obj->value[0] = 1.0;
  obj->value[4] = 0.0;
  obj->value[8] = 0.0;
  obj->value[12] = 0.0;

  obj->value[1] = 0.0;
  obj->value[5] = 1.0;
  obj->value[9] = 0.0;
  obj->value[13] = 0.0;

  obj->value[2] = 0.0;
  obj->value[6] = 0.0;
  obj->value[10] = 1.0;
  obj->value[13] = 0.0;

  obj->value[3] = 0.0;
  obj->value[7] = 0.0;
  obj->value[11] = 0.0;
  obj->value[15] = 1.0;

  return obj;
}

//     col 0 1 2 3
// row
//   0    a11 a12 a13 a14
//   1    a21 a22 a23 a24
//   2
//   3
CMatrix4* cmatrix4_setValues(CMatrix4* obj,
              CMatrixVertexType a11, CMatrixVertexType a12, CMatrixVertexType a13, CMatrixVertexType a14,
              CMatrixVertexType a21, CMatrixVertexType a22, CMatrixVertexType a23, CMatrixVertexType a24,
              CMatrixVertexType a31, CMatrixVertexType a32, CMatrixVertexType a33, CMatrixVertexType a34,
              CMatrixVertexType a41, CMatrixVertexType a42, CMatrixVertexType a43, CMatrixVertexType a44
            ) {
  obj->value[0] = a11;
  obj->value[4] = a12;
  obj->value[8] = a13;
  obj->value[12] = a14;

  obj->value[1] = a21;
  obj->value[5] = a22;
  obj->value[9] = a23;
  obj->value[13] = a24;

  obj->value[2] = a31;
  obj->value[6] = a32;
  obj->value[10] = a33;
  obj->value[14] = a34;

  obj->value[3] = a41;
  obj->value[7] = a42;
  obj->value[11] = a43;
  obj->value[15] = a44;

  return obj;
}

CMatrixVertexType cmatrix4_determinant(CMatrix4* obj) {
  CMatrixVertexType *raw = obj->value;
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


  return -detB123 * raw[12] +
      detB023 * raw[13] -
      detB013 * raw[14] +
      detB012 * raw[15];

}

//
//http://mathworld.wolfram.com/MatrixInverse.html
CMatrixVertexType cmatrix4_inverse(CMatrix4* obj, CMatrix4* outInverse, double *outDeterminant) {
//CMatrixVertexType cmatrix4_inverse(CMatrix4* obj, CMatrix4* out) {
  CMatrixVertexType *raw = obj->value;
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
    return det;
  }
 CMatrixVertexType *outRaw = outInverse->value;
 outRaw[0] = (a11 * b11 - a12 * b10 + a13 * b09)  / det;
 outRaw[1] = (-a01 * b11 + a02 * b10 - a03 * b09) / det;
 outRaw[2] = (a31 * b05 - a32 * b04 + a33 * b03) / det;
 outRaw[3] = (-a21 * b05 + a22 * b04 - a23 * b03) / det;
 outRaw[4] = (-a10 * b11 + a12 * b08 - a13 * b07) / det;
 outRaw[5] = (a00 * b11 - a02 * b08 + a03 * b07) / det;
 outRaw[6] = (-a30 * b05 + a32 * b02 - a33 * b01) / det;
 outRaw[7] = (a20 * b05 - a22 * b02 + a23 * b01) / det;
 outRaw[8] = (a10 * b10 - a11 * b08 + a13 * b06) / det;
 outRaw[9] = (-a00 * b10 + a01 * b08 - a03 * b06) / det;
 outRaw[10] = (a30 * b04 - a31 * b02 + a33 * b00) / det;
 outRaw[11] = (-a20 * b04 + a21 * b02 - a23 * b00) / det;
 outRaw[12] = (-a10 * b09 + a11 * b07 - a12 * b06) / det;
 outRaw[13] = (a00 * b09 - a01 * b07 + a02 * b06) / det;
 outRaw[14] = (-a30 * b03 + a31 * b01 - a32 * b00) / det;
 outRaw[15] = (a20 * b03 - a21 * b01 + a22 * b00) / det;

 return det;
}

CMatrix4* cmatrix4_transpose(CMatrix4* obj, CMatrix4* out) {
  CMatrixVertexType *raw = obj->value;
  double a11 = raw[0];
  double a12 = raw[1];
  double a13 = raw[2];
  double a14 = raw[3];
  double a21 = raw[4];
  double a22 = raw[5];
  double a23 = raw[6];
  double a24 = raw[7];
  double a31 = raw[8];
  double a32 = raw[9];
  double a33 = raw[10];
  double a34 = raw[11];
  double a41 = raw[12];
  double a42 = raw[13];
  double a43 = raw[14];
  double a44 = raw[15];


  obj->value[0] = a11;
  obj->value[4] = a12;
  obj->value[8] = a13;
  obj->value[12] = a14;

  obj->value[1] = a21;
  obj->value[5] = a22;
  obj->value[9] = a23;
  obj->value[13] = a24;

  obj->value[2] = a31;
  obj->value[6] = a32;
  obj->value[10] = a33;
  obj->value[14] = a34;

  obj->value[3] = a41;
  obj->value[7] = a42;
  obj->value[11] = a43;
  obj->value[15] = a44;
  return out;
}
//     col 0 1 2 3
// row
//   0
//   1
//   2
//   3
CMatrixVertexType cmatrix4_getValue(CMatrix4* obj, int row, int col) {
  return obj->value[row+4*col];
}

void cmatrix4_show(CMatrix4* obj){
  for(int i=0;i<4;i++) {
    printf("%f %f %f %lf \r\n",
      cmatrix4_getValue(obj, i, 0),
      cmatrix4_getValue(obj, i, 1),
      cmatrix4_getValue(obj, i, 2),
      cmatrix4_getValue(obj, i, 3));
  }
}

//
// raw
//
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
  double o[16];
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
