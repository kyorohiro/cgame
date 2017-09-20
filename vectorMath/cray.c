#include "cray.h"
#include "cvector3.h"
#include <stdio.h>
#include <math.h>

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
  CVMFloat originX, CVMFloat originY, CVMFloat originZ,
  CVMFloat directionX, CVMFloat directionY, CVMFloat directionZ) {
    initCObject((CObject*)obj, KRAY_NAME);
    CMemory *cmemory = cobject_getCMemory((CObject*)obj);
    obj->origin = initCVector3(newCVector3(cmemory), originX, originY, originZ);
    obj->direction = initCVector3(newCVector3(cmemory), directionX, directionY, directionZ);
    return obj;
}

CRay* createCRay(
  CVMFloat originX, CVMFloat originY, CVMFloat originZ,
  CVMFloat directionX, CVMFloat directionY, CVMFloat directionZ) {
    return initCRay(newCRay(getCMemory()),
    originX, originY, originZ, directionX, directionY, directionZ);
}

CVMFloat cray_intersectsWithTriangle(CRay* obj, CVector3 *p0, CVector3 *p1, CVector3 *p2) {
  return crayraw_intersectsWithTriangle(obj->origin->value, obj->direction->value, p0->value, p1->value, p2->value);
}

void cray_show(CRay* obj) {
  cvector3_show(obj->origin);
  cvector3_show(obj->direction);
}
CVMFloat crayraw_intersectsWithTriangle(CVector3Raw origin, CVector3Raw direction, CVector3Raw p0, CVector3Raw p1, CVector3Raw p2) {

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

    CVMFloat dot = cvector3raw_dotProduct(n, direction);
    if(dot == 0.0){
      return 0.0;
    }

    //printf("dot %f\r\n", dot);
    if(!(dot <0.0f))
    {
      return 0.0f;
    }

    //
    //
    CVMFloat d = cvector3raw_dotProduct(n, p0);
    CVMFloat t = d - cvector3raw_dotProduct(n, origin);
    //printf("t %f\r\n", t);
    if(!(t<=0.0f)) {
      return 0.0f;
    }

    //
    // minT
    //
    // if(!( t >= cvector3raw_dotProduct(minT->value, dot))){
    //  return 0.0f;
    // }

    t /= dot;

    CVector3Raw p;
    cvector3raw_mulScalar(direction, t, p);
    cvector3raw_add(p, origin, p);

    CVMFloat u0, u1, u2;
    CVMFloat v0, v1, v2;
  //  printf("%f %f\r\n",n[1], cmatrixAbs(n[1]));
    if(cmatrixAbs(n[0]) > cmatrixAbs(n[1])){
      if(cmatrixAbs(n[0]) > cmatrixAbs(n[2])){
        u0 = p[1] - p0[1];
        u1 = p1[1] - p0[1];
        u2 = p2[1] - p0[1];
        v0 = p[2] - p0[2];
        v1 = p1[2] - p0[2];
        v2 = p2[2] - p0[2];
      } else {
        u0 = p[0] - p0[0];
        u1 = p1[0] - p0[0];
        u2 = p2[0] - p0[0];
        v0 = p[1] - p0[1];
        v1 = p1[1] - p0[1];
        v2 = p2[1] - p0[1];
      }
    } else {
      if(cmatrixAbs(n[1]) > cmatrixAbs(n[2])){
        u0 = p[0] - p0[0];
        u1 = p1[0] - p0[0];
        u2 = p2[0] - p0[0];
        v0 = p[2] - p0[2];
        v1 = p1[2] - p0[2];
        v2 = p2[2] - p0[2];
      } else {
        u0 = p[0] - p0[0];
        u1 = p1[0] - p0[0];
        u2 = p2[0] - p0[0];
        v0 = p[1] - p0[1];
        v1 = p1[1] - p0[1];
        v2 = p2[1] - p0[1];
      }
    }

    CVMFloat temp = u1*v2-v1*u2;
  //  printf("temp %f\r\n", temp);
    if(!(temp != 0.0f)){
      return 0.0f;
    }
    temp = 1.0f/temp;


    CVMFloat alpha = (u0*v2-v0*u2)*temp;
  //  printf("alpha %f\r\n", alpha);
    if(!(alpha >= 0.0f)){
      return 0.0f;
    }

    CVMFloat beta = (u1*v0-v1*u0)*temp;
  //  printf("beta %f\r\n", beta);
    if(!(beta >= 0.0f)){
      return 0.0f;
    }

    CVMFloat gamma = 1.0f-alpha -beta;
  //  printf("gamma %f\r\n", gamma);
    if(!(gamma >= 0.0f)){
      return 0.0f;
    }

    return t;
}
CVMFloat crayraw_intersectsWithTriangle2(CRay* obj, CVector3Raw p0, CVector3Raw p1, CVector3Raw p2) {

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
