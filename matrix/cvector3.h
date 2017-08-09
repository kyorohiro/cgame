#ifndef __H_GL_VECTOR3_
#define __H_GL_VECTOR3_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "matrix/cmatrix4.h"
#define KVECTOR3_NAME "ve4"

typedef struct {
  CObject parent;
  CMatrixValue value[3];
} CVector3;

CVector3* newCVector3(CMemory*);
CVector3* initCVector3(CVector3*, CMatrixValue v0, CMatrixValue v1, CMatrixValue v2);

CVector3* cvector3_crossProduct(CVector3* obj, CVector3* arg, CVector3* out);
CMatrixValue cvector3_normalize(CVector3* obj);
CVector3* cvector3_add(CVector3* obj, CVector3* arg, CVector3* out);
CVector3* cvector3_sub(CVector3* obj, CVector3* arg, CVector3* out);
/*
CMatrix4* cmatrix4_add(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_sub(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_outer(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrixValue cmatrix4_getValue(CMatrix4* obj, int i, int j);
void cmatrix4_show(CMatrix4* obj);
*/
#endif
