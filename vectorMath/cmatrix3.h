
#ifndef __H_GL_MATRIX3_
#define __H_GL_MATRIX3_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvector3.h"
#include "cmatrix_inner.h"

#define KMATRIX_NAME "kma"

typedef CMatrixValueType CMatrix3Raw[9];
typedef CMatrixValueType *CMatrix3RawRef;

typedef struct {
  CObject parent;
  CMatrix3Raw value;
} CMatrix3;

CMatrix3* newCMatrix3(CMemory*);
CMatrix3* initCMatrix3(CMatrix3*);
CMatrix3* cmatrix3_setIdentity(CMatrix3* obj);
CMatrix3* cmatrix3_setValues(CMatrix3* obj,
              CMatrixValueType a11, CMatrixValueType a12, CMatrixValueType a13,
              CMatrixValueType a21, CMatrixValueType a22, CMatrixValueType a23,
              CMatrixValueType a31, CMatrixValueType a32, CMatrixValueType a33);

CMatrix3* cmatrix3_add(CMatrix3* obj, CMatrix3* arg, CMatrix3* out);
CMatrix3* cmatrix3_sub(CMatrix3* obj, CMatrix3* arg, CMatrix3* out);
CMatrix3* cmatrix3_mul(CMatrix3* obj, CMatrix3* arg, CMatrix3* out);
CVector3* cmatrix3_mulCVector3(CMatrix3* obj, CVector3* arg, CVector3* out);
CMatrix3* cmatrix3_transpose(CMatrix3* obj, CMatrix3* out);
CMatrixValueType cmatrix3_determinant(CMatrix3* obj);
CMatrix3* cmatrix3_inverse(CMatrix3* obj, CMatrix3* outInverse, CMatrixValueType *outDeterminant);

//     col 0 1 2 3
// row
//   0
//   1
//   2
//   3
CMatrixValueType cmatrix3_getValue(CMatrix3* obj, int row, int col);
void cmatrix3_show(CMatrix3* obj);


//
//
// RAW
//
//
CMatrix3RawRef cmatrix3raw_setIdentity(CMatrix3RawRef obj);

CMatrix3RawRef cmatrix3raw_setValues(CMatrix3RawRef obj,
              CMatrixValueType a11, CMatrixValueType a12, CMatrixValueType a13,
              CMatrixValueType a21, CMatrixValueType a22, CMatrixValueType a23,
              CMatrixValueType a31, CMatrixValueType a32, CMatrixValueType a33
            );
CMatrix3RawRef cmatrix3raw_copy(CMatrix3RawRef obj, CMatrix3RawRef out);
CMatrix3RawRef cmatrix3raw_add(CMatrix3RawRef obj, CMatrix3RawRef arg, CMatrix3RawRef out);
CMatrix3RawRef cmatrix3raw_sub(CMatrix3RawRef obj, CMatrix3RawRef arg, CMatrix3RawRef out);
CMatrix3RawRef cmatrix3raw_mul(CMatrix3RawRef obj, CMatrix3RawRef arg, CMatrix3RawRef out);
CVector3RawRef cmatrix3raw_mulVector3Raw(CMatrix3RawRef obj, CVector3RawRef arg, CVector3RawRef out);
CVector3RawRef cmatrix3raw_mulVector(CMatrix3RawRef obj, CMatrixValueType x, CMatrixValueType y, CMatrixValueType z, CVector3RawRef out);

CMatrix3RawRef cmatrix3raw_transpose(CMatrix3RawRef obj, CMatrix3RawRef out);
CMatrixValueType cmatrix3raw_determinant(CMatrix3RawRef obj);
CMatrix3RawRef cmatrix3raw_inverse(CMatrix3RawRef obj, CMatrix3RawRef outInverse, CMatrixValueType *outDeterminant);

CMatrixValueType cmatrix3raw_getValue(CMatrix3RawRef obj, int row, int col);
void cmatrix3raw_show(CMatrix3RawRef obj);
#endif
