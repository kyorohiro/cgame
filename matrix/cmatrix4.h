
#ifndef __H_GL_MATRIX_
#define __H_GL_MATRIX_

#include "core/cobject.h"
#include "core/cmemory.h"

#define KMATRIX_NAME "kma"

typedef float KValue;
typedef struct {
  CObject parent;
  KValue value[16];
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
              KValue a11, KValue a12, KValue a13, KValue a14,
              KValue a21, KValue a22, KValue a23, KValue a24,
              KValue a31, KValue a32, KValue a33, KValue a34,
              KValue a41, KValue a42, KValue a43, KValue a44
            );

//CMatrix4* setRotateX(CMatrix4* obj, double angle);

CMatrix4* cmatrix4_add(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_sub(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_outer(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
KValue cmatrix4_getValue(CMatrix4* obj, int i, int j);

#endif
