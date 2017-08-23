
#ifndef __H_GL_CRAY_
#define __H_GL_CRAY_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvector3.h"
#include "cmatrix_inner.h"



#define KRAY_NAME "ray"

typedef struct {
  CObject parent;
  CVector3* origin;
  CVector3* direction;
} CRay;

CRay* newCRay(CMemory*);
CRay* initCRay(CRay*,
  CMatrixVertexType originX, CMatrixVertexType originY, CMatrixVertexType originZ,
  CMatrixVertexType directionX, CMatrixVertexType directionY, CMatrixVertexType directionZ);
CMatrixVertexType cray_intersectsWithTriangle(CRay* obj, CVector3 *p0, CVector3 *p1, CVector3 *p2);
void cray_show(CRay* obj);
CMatrixVertexType crayraw_intersectsWithTriangle2(CRay* obj, CVector3Raw p0, CVector3Raw p1, CVector3Raw p2);
CMatrixVertexType crayraw_intersectsWithTriangle(CRay* obj, CVector3Raw p0, CVector3Raw p1, CVector3Raw p2);
#endif
