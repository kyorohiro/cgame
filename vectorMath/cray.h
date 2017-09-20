
#ifndef __H_CRay
#define __H_CRay

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvector3.h"
#include "cvectorMath_inner.h"


typedef struct {
  CObject parent;
  CVector3* origin;
  CVector3* direction;
} CRay;

CRay* newCRay(CMemory*);
CRay* initCRay(CRay*,
  CVMFloat originX, CVMFloat originY, CVMFloat originZ,
  CVMFloat directionX, CVMFloat directionY, CVMFloat directionZ);

CRay* createCRay(
  CVMFloat originX, CVMFloat originY, CVMFloat originZ,
  CVMFloat directionX, CVMFloat directionY, CVMFloat directionZ);

CVMFloat cray_intersectsWithTriangle(CRay* obj, CVector3 *p0, CVector3 *p1, CVector3 *p2);
void cray_show(CRay* obj);
CVMFloat crayraw_intersectsWithTriangle2(CRay* obj, CVector3Raw p0, CVector3Raw p1, CVector3Raw p2);
CVMFloat crayraw_intersectsWithTriangle(CVector3Raw origin, CVector3Raw direction, CVector3Raw p0, CVector3Raw p1, CVector3Raw p2);
#endif
