#ifndef __H_GL_VECTOR4_
#define __H_GL_VECTOR4_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "matrix/cmatrix4.h"
#define KVECTOR4_NAME "ve4"

typedef struct {
  CObject parent;
  CMatrixValue value[4];
} CVector4;

CVector4* newCVector4(CMemory*);
CVector4* initCVector4(CVector4*, CMatrixValue v0, CMatrixValue v1, CMatrixValue v2, CMatrixValue v3);

/*
CMatrix4* cmatrix4_add(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_sub(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_multiply(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrixValue cmatrix4_getValue(CMatrix4* obj, int i, int j);
void cmatrix4_show(CMatrix4* obj);
*/
#endif
