
#ifndef __H_GL_MATRIX_
#define __H_GL_MATRIX_

#include "core/object.h"
#include "core/cmemory.h"

#define KMATRIX_NAME "kma"

typedef float KValue;
typedef struct {
  CObject parent;
  KValue value[16];
} KMatrix;

KMatrix* newKMatrix();
KMatrix* initKMatrix(KMatrix*);


//KMatrix* freeMatrix(KMatrix* obj);
KMatrix* kmatrix_setIdentity(KMatrix* obj);
KMatrix* kmatrix_setRotationX(KMatrix* obj, double radians);
KMatrix* kmatrix_setRotationY(KMatrix* obj, double radians);
KMatrix* kmatrix_setRotationZ(KMatrix* obj, double radians);
//KMatrix* setRotateX(KMatrix* obj, double angle);

KMatrix* kmatrix_add(KMatrix* obj, KMatrix* arg, KMatrix* out);
KMatrix* kmatrix_sub(KMatrix* obj, KMatrix* arg, KMatrix* out);
KMatrix* kmatrix_outer(KMatrix* obj, KMatrix* arg, KMatrix* out);

#endif
