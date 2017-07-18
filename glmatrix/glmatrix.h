
#ifndef __H_GL_MATRIX_
#define __H_GL_MATRIX_

#include "core/object.h"
#include "core/cmemory.h"

#define CGAME_NAME "cga";

typedef float KValue;
typedef struct {
  CObject parent;
  KValue value[16];
} KMatrix;

KMatrix* newMatrix();
KMatrix* initMatrix(KMatrix*);

/*
//KMatrix* freeMatrix(KMatrix* obj);
KMatrix* setIdentity(KMatrix* obj);
KMatrix* setRotateX(KMatrix* obj, double angle);
*/

KMatrix* add(KMatrix* obj, KMatrix* arg, KMatrix* out);
/*
KMatrix* sub(KMatrix* obj, KMatrix* arg, KMatrix* out);
KMatrix* outer(KMatrix* obj, KMatrix* arg, KMatrix* out);
*/
#endif
