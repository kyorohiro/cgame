
#ifndef __H_GL_MATRIX4_
#define __H_GL_MATRIX4_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvector4.h"
#include "cmatrix_inner.h"



#define KMATRIX_NAME "kma"

typedef struct {
  CObject parent;
  CMatrixValue value[16];
} CMatrix4;

CMatrix4* newCMatrix4(CMemory*);
CMatrix4* initCMatrix4(CMatrix4*);


//CMatrix4* freeMatrix(CMatrix4* obj);
CMatrix4* cmatrix4_setIdentity(CMatrix4* obj);

CMatrix4* cmatrix4_setValues(CMatrix4* obj,
              CMatrixValue a11, CMatrixValue a12, CMatrixValue a13, CMatrixValue a14,
              CMatrixValue a21, CMatrixValue a22, CMatrixValue a23, CMatrixValue a24,
              CMatrixValue a31, CMatrixValue a32, CMatrixValue a33, CMatrixValue a34,
              CMatrixValue a41, CMatrixValue a42, CMatrixValue a43, CMatrixValue a44
            );
//CMatrix4* setRotateX(CMatrix4* obj, double angle);

CMatrix4* cmatrix4_add(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_sub(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_multiply(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CVector4* cmatrix4_multiplyCVector4(CMatrix4* obj, CVector4* arg, CVector4* out);
//     col 0 1 2 3
// row
//   0
//   1
//   2
//   3
CMatrixValue cmatrix4_getValue(CMatrix4* obj, int row, int col);
void cmatrix4_show(CMatrix4* obj);
#endif
