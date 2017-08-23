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
  return crayraw_intersectsWithTriangle(obj, p0->value, p1->value, p2->value);
}

void cray_show(CRay* obj) {
  cvector3_show(obj->origin);
  cvector3_show(obj->direction);
}

CMatrixVertexType crayraw_intersectsWithTriangle(CRay* obj, CVector3Raw p0, CVector3Raw p1, CVector3Raw p2) {

    CVector3Raw e1;
    CVector3Raw e2;
    CVector3Raw n;
    cvector3raw_sub(p1, p0, e1);
    cvector3raw_sub(p2, p1, e2);
    cvector3raw_crossProduct(e1, e2, n);

    //
    //
    /*
    cvector3raw_show(n);
    cvector3raw_show(obj->direction->value);
    cvector3raw_show(e1);
    cvector3raw_show(e2);
    cvector3raw_show(p0);
    cvector3raw_show(p1);
    cvector3raw_show(p2);*/

    CMatrixValueType dot = cvector3raw_dotProduct(n, obj->direction->value);
    if(dot == 0.0){
      return 0.0;
    }
    /*
    if(!(dot <0.0f)){
      printf("dot %f\r\n", dot);
      return 0.0f;
    }
*/
    //
    //
    CMatrixValueType d = cvector3raw_dotProduct(n, p0);
    CMatrixValueType t = d - cvector3raw_dotProduct(n, obj->origin->value);
  /*  if(!(t<=0.0f)) {
      printf("t %f\r\n", t);
      return 0.0f;
    }*/

    //
    // minT
    //
    // if(!( t >= cvector3raw_dotProduct(minT->value, dot))){
    //  return 0.0f;
    // }

    return t /= dot;
}
CMatrixVertexType crayraw_intersectsWithTriangle2(CRay* obj, CVector3Raw p0, CVector3Raw p1, CVector3Raw p2) {

  CVector3Raw triV1;
  CVector3Raw triV2;
  CVector3Raw cd20;
  cvector3raw_sub(p1, p0, triV1);
  cvector3raw_sub(p2, p0, triV2);
  cvector3raw_crossProduct(obj->direction->value, triV2, cd20);
  double a = cvector3raw_dotProduct(triV1, cd20);
  //
  // todo check a

  CVector3Raw o0;
  cvector3raw_sub(obj->origin->value, p0, o0);
  double u = 1/a * cvector3raw_dotProduct(o0, triV1);

  if (u < 0.0) {
     return 0.0;
   }

  CVector3Raw _r;
  cvector3raw_crossProduct(o0, triV1, _r);
  double v = 1/a * cvector3raw_dotProduct(obj->direction->value, _r);
   //
   // todo check r
  return 1/a * cvector3raw_dotProduct(triV1
    ,_r);
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
