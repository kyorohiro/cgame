
#ifndef __H_GL_MATRIX_
#define __H_GL_MATRIX_

#include "core/cobject.h"
#include "core/cmemory.h"

#define KMATRIX_NAME "kma"

typedef float KValue;
typedef struct {
  CObject parent;
  KValue value[16];
} CMatrix;

CMatrix* newCMatrix();
CMatrix* initCMatrix(CMatrix*);


//CMatrix* freeMatrix(CMatrix* obj);
CMatrix* cmatrix_setIdentity(CMatrix* obj);
CMatrix* cmatrix_setRotationX(CMatrix* obj, double radians);
CMatrix* cmatrix_setRotationY(CMatrix* obj, double radians);
CMatrix* cmatrix_setRotationZ(CMatrix* obj, double radians);
CMatrix* cmatrix_setTranslation(CMatrix* obj, double x, double y, double z);
CMatrix* cmatrix_setScale(CMatrix* obj, double x, double y, double z);
//CMatrix* setRotateX(CMatrix* obj, double angle);

CMatrix* cmatrix_add(CMatrix* obj, CMatrix* arg, CMatrix* out);
CMatrix* cmatrix_sub(CMatrix* obj, CMatrix* arg, CMatrix* out);
CMatrix* cmatrix_outer(CMatrix* obj, CMatrix* arg, CMatrix* out);

#endif
