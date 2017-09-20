
#ifndef __H_CMatrix4
#define __H_CMatrix4


#include "core/cobject.h"
#include "core/cmemory.h"
#include "cmatrix_inner.h"
#include "cvector4.h"


typedef CMatrixValueType CMatrix4Raw[16];
typedef CMatrixValueType *CMatrix4RawRef;

typedef struct {
  CObject parent;
  CMatrix4Raw value;
} CMatrix4;

CMatrix4* newCMatrix4(CMemory*);
CMatrix4* initCMatrix4(CMatrix4*);
CMatrix4* createCMatrix4();
CMatrix4* cmatrix4_setIdentity(CMatrix4* obj);
CMatrix4* cmatrix4_setValues(CMatrix4* obj,
              CMatrixValueType a11, CMatrixValueType a12, CMatrixValueType a13, CMatrixValueType a14,
              CMatrixValueType a21, CMatrixValueType a22, CMatrixValueType a23, CMatrixValueType a24,
              CMatrixValueType a31, CMatrixValueType a32, CMatrixValueType a33, CMatrixValueType a34,
              CMatrixValueType a41, CMatrixValueType a42, CMatrixValueType a43, CMatrixValueType a44);

CMatrix4* cmatrix4_add(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_sub(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_mul(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CVector4* cmatrix4_mulCVector4(CMatrix4* obj, CVector4* arg, CVector4* out);
CMatrix4* cmatrix4_transpose(CMatrix4* obj, CMatrix4* out);
CMatrixValueType cmatrix4_determinant(CMatrix4* obj);
CMatrix4* cmatrix4_inverse(CMatrix4* obj, CMatrix4* outInverse, CMatrixValueType *outDeterminant);

//     col 0 1 2 3
// row
//   0
//   1
//   2
//   3
CMatrixValueType cmatrix4_getValue(CMatrix4* obj, int row, int col);
void cmatrix4_show(CMatrix4* obj);


//
//
// RAW
//
//
CMatrix4RawRef cmatrix4raw_setIdentity(CMatrix4RawRef obj);

CMatrix4RawRef cmatrix4raw_setValues(CMatrix4RawRef obj,
              CMatrixValueType a11, CMatrixValueType a12, CMatrixValueType a13, CMatrixValueType a14,
              CMatrixValueType a21, CMatrixValueType a22, CMatrixValueType a23, CMatrixValueType a24,
              CMatrixValueType a31, CMatrixValueType a32, CMatrixValueType a33, CMatrixValueType a34,
              CMatrixValueType a41, CMatrixValueType a42, CMatrixValueType a43, CMatrixValueType a44
            );
CMatrix4RawRef cmatrix4raw_copy(CMatrix4RawRef obj, CMatrix4RawRef out);
CMatrix4RawRef cmatrix4raw_add(CMatrix4RawRef obj, CMatrix4RawRef arg, CMatrix4RawRef out);
CMatrix4RawRef cmatrix4raw_sub(CMatrix4RawRef obj, CMatrix4RawRef arg, CMatrix4RawRef out);
CMatrix4RawRef cmatrix4raw_mul(CMatrix4RawRef obj, CMatrix4RawRef arg, CMatrix4RawRef out);
CVector4RawRef cmatrix4raw_mulVector4Raw(CMatrix4RawRef obj, CVector4RawRef arg, CVector4RawRef out);
CVector4RawRef cmatrix4raw_mulVector(CMatrix4RawRef obj, CMatrixValueType x,  CMatrixValueType y, CMatrixValueType z, CMatrixValueType w, CVector4RawRef out);

CMatrix4RawRef cmatrix4raw_transpose(CMatrix4RawRef obj, CMatrix4RawRef out);
CMatrixValueType cmatrix4raw_determinant(CMatrix4RawRef obj);
CMatrix4RawRef cmatrix4raw_inverse(CMatrix4RawRef obj, CMatrix4RawRef outInverse, CMatrixValueType *outDeterminant);


CMatrixValueType cmatrix4raw_getValue(CMatrix4RawRef obj, int row, int col);
void cmatrix4raw_show(CMatrix4RawRef obj);

#endif
