#include "cray.h"
#include "cvector3.h"
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
  CMatrixVertexType originX, CMatrixVertexType originY, CMatrixVertexType originZ,
  CMatrixVertexType directionX, CMatrixVertexType directionY, CMatrixVertexType directionZ) {
    initCObject((CObject*)obj, KRAY_NAME);
    CMemory *cmemory = cobject_getCMemory((CObject*)obj);
    obj->origin = initCVector3(newCVector3(cmemory), originX, originY, originZ);
    obj->direction = initCVector3(newCVector3(cmemory), directionX, directionY, directionZ);
    return obj;
}

CMatrixVertexType cray_intersectsWithTriangle(CRay* obj, CVector3 *p0, CVector3 *p1, CVector3 *p2) {

  CVector3Raw e1;
  CVector3Raw e2;
  CVector3Raw n;
  cvector3raw_sub(p1->value, p0->value, e1);
  cvector3raw_sub(p1->value, p0->value, e2);
  cvector3raw_crossProduct(e1, e2, n);

  //
  //
  CMatrixValueType dot = cvector3raw_dotProduct(n, obj->direction->value);
  if(!(dot <0.0f)){
    return 0.0f;
  }
  //
  //
  CMatrixValueType d = cvector3raw_dotProduct(n, p0->value);
  CMatrixValueType t = d - cvector3raw_dotProduct(n, obj->origin->value);
  if(!(t<=0.0f)) {
    return 0.0f;
  }

  //
  // minT
  //
  // if(!( t >= cvector3raw_dotProduct(minT->value, dot))){
  //  return 0.0f;
  // }

  return t /= dot;
}

/*
CMatrixVertexType cray_intersectsWithTriangle(CRay* obj, CVector3 *p0, CVector3 *p1, CVector3 *p2) {

  CVector3* triV1 = cvector3_sub(p1, p0, NULL);
  CVector3* triV2 = cvector3_sub(p2, p0, NULL);
  CVector3* cd20 = cvector3_crossProduct(obj->direction, triV2, NULL);
  double a = cvector3_dotProduct(triV1, cd20);
  //
  // todo check a
  if(a )

  CVector3* o0 = cvector3_sub(obj->origin, p0, NULL);
  double u = 1/a * cvector3_dotProduct(o0, triV1);

  if (u < 0.0) {
     return 0.0;
   }

  CVector3* _r = cvector3_crossProduct(o0, triV1, NULL);
  double v = 1/a * cvector3_dotProduct(obj->direction, _r);
   //
   // todo check r
  return 1/a * cvector3_dotProduct(triV1
    ,_r);
}
*/
