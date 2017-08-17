
#ifndef __H_GL_CRAY_
#define __H_GL_CRAY_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvector4.h"
#include "cmatrix_inner.h"



#define KRAY_NAME "ray"

typedef struct {
  CObject parent;
  CVector4* origin;
  CVector4* target;
} CRay;

CRay* newCRay(CMemory*);
CRay* initCRay(CRay*, CMatrixValue originX, CMatrixValue originY, CMatrixValue originZ,
CMatrixValue targetX, CMatrixValue targetY, CMatrixValue targetZ);


#endif
