
#ifndef __H_GL_MATRIX2_
#define __H_GL_MATRIX2_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvector2.h"
#include "cmatrix_inner.h"

#define KMATRIX_NAME "kma"

typedef CMatrixValueType CMatrix2Raw[4];
typedef CMatrixValueType *CMatrix2RawRef;

typedef struct {
  CObject parent;
  CMatrix2Raw value;
} CMatrix2;

CMatrix2* newCMatrix2(CMemory*);
CMatrix2* initCMatrix2(CMatrix2*);
CMatrix2* cmatrix2_setIdentity(CMatrix2* obj);
CMatrix2* cmatrix2_setValues(CMatrix2* obj,
              CMatrixValueType a11, CMatrixValueType a12,
              CMatrixValueType a21, CMatrixValueType a22);

CMatrix2* cmatrix2_add(CMatrix2* obj, CMatrix2* arg, CMatrix2* out);
CMatrix2* cmatrix2_sub(CMatrix2* obj, CMatrix2* arg, CMatrix2* out);
CMatrix2* cmatrix2_mul(CMatrix2* obj, CMatrix2* arg, CMatrix2* out);
CVector2* cmatrix2_mulCVector2(CMatrix2* obj, CVector2* arg, CVector2* out);
CMatrix2* cmatrix2_transpose(CMatrix2* obj, CMatrix2* out);
CMatrixValueType cmatrix2_determinant(CMatrix2* obj);
CMatrix2* cmatrix2_inverse(CMatrix2* obj, CMatrix2* outInverse, CMatrixValueType *outDeterminant);

//     col 0 1 2 3
// row
//   0
//   1
//   2
//   3
CMatrixValueType cmatrix2_getValue(CMatrix2* obj, int row, int col);
void cmatrix2_show(CMatrix2* obj);


//
//
// RAW
//
//
CMatrix2RawRef cmatrix2raw_setIdentity(CMatrix2RawRef obj);

CMatrix2RawRef cmatrix2raw_setValues(CMatrix2RawRef obj,
              CMatrixValueType a11, CMatrixValueType a12,
              CMatrixValueType a21, CMatrixValueType a22);
CMatrix2RawRef cmatrix2raw_copy(CMatrix2RawRef obj, CMatrix2RawRef out);
CMatrix2RawRef cmatrix2raw_add(CMatrix2RawRef obj, CMatrix2RawRef arg, CMatrix2RawRef out);
CMatrix2RawRef cmatrix2raw_sub(CMatrix2RawRef obj, CMatrix2RawRef arg, CMatrix2RawRef out);
CMatrix2RawRef cmatrix2raw_mul(CMatrix2RawRef obj, CMatrix2RawRef arg, CMatrix2RawRef out);
CVector2RawRef cmatrix2raw_mulVector2Raw(CMatrix2RawRef obj, CVector2RawRef arg, CVector2RawRef out);
CVector2RawRef cmatrix2raw_mulVector(CMatrix2RawRef obj, CMatrixValueType x, CMatrixValueType y, CVector2RawRef out);

CMatrix2RawRef cmatrix2raw_transpose(CMatrix2RawRef obj, CMatrix2RawRef out);
CMatrixValueType cmatrix2raw_determinant(CMatrix2RawRef obj);
CMatrix2RawRef cmatrix2raw_inverse(CMatrix2RawRef obj, CMatrix2RawRef outInverse, CMatrixValueType *outDeterminant);

CMatrixValueType cmatrix2raw_getValue(CMatrix2RawRef obj, int row, int col);
void cmatrix2raw_show(CMatrix2RawRef obj);
#endif
