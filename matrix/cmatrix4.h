
#ifndef __H_GL_MATRIX_
#define __H_GL_MATRIX_

#include "core/cobject.h"
#include "core/cmemory.h"

#define KMATRIX_NAME "kma"

typedef float CMatrixValue;
typedef short CIndexValue;
typedef struct {
  CObject parent;
  CMatrixValue value[16];
} CMatrix4;

CMatrix4* newCMatrix4(CMemory*);
CMatrix4* initCMatrix4(CMatrix4*);


//CMatrix4* freeMatrix(CMatrix4* obj);
CMatrix4* cmatrix4_setIdentity(CMatrix4* obj);
CMatrix4* cmatrix4_setRotationX(CMatrix4* obj, double radians);
CMatrix4* cmatrix4_setRotationY(CMatrix4* obj, double radians);
CMatrix4* cmatrix4_setRotationZ(CMatrix4* obj, double radians);
CMatrix4* cmatrix4_setTranslation(CMatrix4* obj, double x, double y, double z);
CMatrix4* cmatrix4_setScale(CMatrix4* obj, double x, double y, double z);
CMatrix4* cmatrix4_setValues(CMatrix4* obj,
              CMatrixValue a11, CMatrixValue a12, CMatrixValue a13, CMatrixValue a14,
              CMatrixValue a21, CMatrixValue a22, CMatrixValue a23, CMatrixValue a24,
              CMatrixValue a31, CMatrixValue a32, CMatrixValue a33, CMatrixValue a34,
              CMatrixValue a41, CMatrixValue a42, CMatrixValue a43, CMatrixValue a44
            );
CMatrix4* cmatrix4_setOrthogonalProjection(CMatrix4* obj, double right, double left, double top, double bottom, double far, double near);
CMatrix4* cmatrix4_setPerspectiveProjection(CMatrix4* obj, double right, double left, double top, double bottom, double far, double near);

//CMatrix4* setRotateX(CMatrix4* obj, double angle);

CMatrix4* cmatrix4_add(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_sub(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_outer(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrixValue cmatrix4_getValue(CMatrix4* obj, int i, int j);
void cmatrix4_show(CMatrix4* obj);
#endif
