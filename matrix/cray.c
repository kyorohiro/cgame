#include "cray.h"
#include <stdio.h>

void _freeCRay(void* obj) {
  if(obj == NULL) {
    return;
  }
  CRay* rayObj = (CRay*)obj;
  releaseCObject((CObject*)rayObj->origin);
  releaseCObject((CObject*)rayObj->direction);
  freeCObject(obj);
}

CRay* newCRay(CMemory* cmemory) {
  CRay* obj = cmemory_calloc(cmemory, 1, sizeof(CRay));
  ((CObject*)obj)->cmemory = cmemory;
  ((CObject*)obj)->funcFree = _freeCRay;
  return obj;
}

CRay* initCRay(CRay* obj,
  CMatrixValue originX, CMatrixValue originY, CMatrixValue originZ,
  CMatrixValue directionX, CMatrixValue directionY, CMatrixValue directionZ) {
    initCObject((CObject*)obj, KRAY_NAME);
    CMemory *cmemory = cobject_getCMemory((CObject*)obj);
    obj->origin = initCVector3(newCVector3(cmemory), originX, originY, originZ);
    obj->direction = initCVector3(newCVector3(cmemory), directionX, directionY, directionZ);
    return obj;
}

CMatrixValue cray_intersectsWithTriangle(CRay* obj, CVector3 *p0, CVector3 *p1, CVector3 *p2) {

  CVector3* p10 = cvector3_sub(p1, p0, NULL);
  CVector3* p20 = cvector3_sub(p2, p0, NULL);
  CVector3* cd20 = cvector3_crossProduct(obj->direction, p20, NULL);
  double a = cvector3_dotProduct(p10, cd20);
  //
  // todo check a

  CVector3* o0 = cvector3_sub(obj->origin, p0, NULL);
  double u = 1/a * cvector3_dotProduct(o0, cd20);

  if (u < 0.0) {
     return 0.0;
   }

  CVector3* _r = cvector3_crossProduct(o0, p10, NULL);
  double v = 1/a * cvector3_dotProduct(obj->direction, _r);
   //
   // todo check r
  return 1/a * cvector3_dotProduct(p20,_r);
}
