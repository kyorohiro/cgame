#ifndef __H_GL_VECTOR3_
#define __H_GL_VECTOR3_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cmatrix_inner.h"
#define KVECTOR3_NAME "ve4"

typedef CMatrixValue CVector3Raw[3];

typedef struct {
  CObject parent;
  CVector3Raw value;
} CVector3;

CVector3* newCVector3(CMemory*);
CVector3* initCVector3(CVector3*, CMatrixValue v0, CMatrixValue v1, CMatrixValue v2);

CVector3* cvector3_crossProduct(CVector3* obj, CVector3* arg, CVector3* out);
CMatrixValue cvector3_dotProduct(CVector3* obj, CVector3* arg);
CMatrixValue cvector3_normalize(CVector3* obj);
CVector3* cvector3_add(CVector3* obj, CVector3* arg, CVector3* out);
CVector3* cvector3_sub(CVector3* obj, CVector3* arg, CVector3* out);

CVector3Raw* cvector3raw_crossProduct(CVector3Raw *obj, CVector3Raw *arg, CVector3Raw *out);
CMatrixValue cvector3raw_dotProduct(CVector3Raw* obj, CVector3Raw* arg);
#endif
