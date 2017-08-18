
#ifndef __H_GL_MATRIX4_
#define __H_GL_MATRIX4_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvector4.h"
#include "cmatrix_inner.h"

#define KMATRIX_NAME "kma"

typedef CMatrixValueType CMatrix4Raw[16];
typedef CMatrixValueType *CMatrix4RawRef;

typedef struct {
  CObject parent;
  CMatrix4Raw value;
} CMatrix4;

CMatrix4* newCMatrix4(CMemory*);
CMatrix4* initCMatrix4(CMatrix4*);


//CMatrix4* freeMatrix(CMatrix4* obj);
CMatrix4* cmatrix4_setIdentity(CMatrix4* obj);

CMatrix4* cmatrix4_setValues(CMatrix4* obj,
              CMatrixVertexType a11, CMatrixVertexType a12, CMatrixVertexType a13, CMatrixVertexType a14,
              CMatrixVertexType a21, CMatrixVertexType a22, CMatrixVertexType a23, CMatrixVertexType a24,
              CMatrixVertexType a31, CMatrixVertexType a32, CMatrixVertexType a33, CMatrixVertexType a34,
              CMatrixVertexType a41, CMatrixVertexType a42, CMatrixVertexType a43, CMatrixVertexType a44
            );
//CMatrix4* setRotateX(CMatrix4* obj, double angle);

CMatrix4* cmatrix4_add(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_sub(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_multiply(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CVector4* cmatrix4_multiplyCVector4(CMatrix4* obj, CVector4* arg, CVector4* out);
CMatrix4* cmatrix4_transpose(CMatrix4* obj, CMatrix4* out);
CMatrixVertexType cmatrix4_determinant(CMatrix4* obj);
CMatrixVertexType cmatrix4_inverse(CMatrix4* obj, CMatrix4* outInverse, double* outDeterminant);
//     col 0 1 2 3
// row
//   0
//   1
//   2
//   3
CMatrixVertexType cmatrix4_getValue(CMatrix4* obj, int row, int col);
void cmatrix4_show(CMatrix4* obj);

//
// RAW
//
CMatrix4RawRef cmatrix4raw_add(CMatrix4RawRef obj, CMatrix4RawRef arg, CMatrix4RawRef out);
CMatrix4RawRef cmatrix4raw_sub(CMatrix4RawRef obj, CMatrix4RawRef arg, CMatrix4RawRef out);
CMatrix4RawRef cmatrix4raw_mul(CMatrix4RawRef obj, CMatrix4RawRef arg, CMatrix4RawRef out);
CVector4RawRef cmatrix4_mulVector4Raw(CMatrix4RawRef obj, CVector4RawRef arg, CVector4RawRef out);
#endif
