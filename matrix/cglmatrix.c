#include "cmatrix4.h"
#include "cvector3.h"
#include "cglmatrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// c 0 s
// 0 1 0
//-s 0 c
CMatrix4* cmatrix4_setRotationY(CMatrix4* obj, double radians){
  double c = cos(radians);
  double s = sin(radians);
  obj->value[0] = c;
  obj->value[4] = 0.0;
  obj->value[8] = s;
  obj->value[12] = 0.0;

  obj->value[1] = 0.0;
  obj->value[5] = 1.0;
  obj->value[9] = 0.0;
  obj->value[13] = 0.0;

  obj->value[2] =  -s;
  obj->value[6] = 0.0;
  obj->value[10] = c;
  obj->value[14] = 0.0;

  obj->value[3] = 0.0;
  obj->value[7] = 0.0;
  obj->value[11] = 0.0;
  obj->value[15] = 1.0;
  return obj;
}

// 1 0 0
// 0 c -s
// 0 s c
CMatrix4* cmatrix4_setRotationX(CMatrix4* obj, double radians){
  double c = cos(radians);
  double s = sin(radians);

  obj->value[0] = 1;
  obj->value[4] = 0.0;
  obj->value[8] = 0.0;
  obj->value[12] = 0.0;

  obj->value[1] = 0.0;
  obj->value[5] = c;
  obj->value[9] = -s;
  obj->value[13] = 0.0;

  obj->value[2] = 0.0;
  obj->value[6] =  s;
  obj->value[10] = c;
  obj->value[14] = 0.0;

  obj->value[3] = 0.0;
  obj->value[7] = 0.0;
  obj->value[11] = 0.0;
  obj->value[15] = 1.0;
  return obj;
}

// 1 0 0
// 0 c -s
// 0 s c
CMatrix4* cmatrix4_setRotationZ(CMatrix4* obj, double radians){
  double c = cos(radians);
  double s = sin(radians);
  obj->value[0] = c;
  obj->value[4] = -s;
  obj->value[8] = 0.0;
  obj->value[12] = 0.0;

  obj->value[1] = s;
  obj->value[5] = c;
  obj->value[9] = 0.0;
  obj->value[13] = 0.0;

  obj->value[2] = 0.0;
  obj->value[6] = 0.0;
  obj->value[10] = 1.0;
  obj->value[14] = 0.0;

  obj->value[3] = 0.0;
  obj->value[7] = 0.0;
  obj->value[11] = 0.0;
  obj->value[15] = 1.0;
  return obj;
}

CMatrix4* cmatrix4_setTranslation(CMatrix4* obj, double x, double y, double z) {
  obj->value[0] = 1.0;
  obj->value[4] = 0.0;
  obj->value[8] = 0.0;
  obj->value[12] = x;

  obj->value[1] = 0.0;
  obj->value[5] = 1.0;
  obj->value[9] = 0.0;
  obj->value[13] = y;

  obj->value[2] = 0.0;
  obj->value[6] = 0.0;
  obj->value[10] = 1.0;
  obj->value[14] = z;

  obj->value[3] = 0.0;
  obj->value[7] = 0.0;
  obj->value[11] = 0.0;
  obj->value[15] = 1.0;
  return obj;
}

CMatrix4* cmatrix4_setScale(CMatrix4* obj, double x, double y, double z) {
  obj->value[0] = x;
  obj->value[4] = 0.0;
  obj->value[8] = 0.0;
  obj->value[12] = 0.0;

  obj->value[1] = y;
  obj->value[5] = 1.0;
  obj->value[9] = 0.0;
  obj->value[13] = 0.0;

  obj->value[2] = 0.0;
  obj->value[6] = 0.0;
  obj->value[10] = z;
  obj->value[14] = 0.0;

  obj->value[3] = 0.0;
  obj->value[7] = 0.0;
  obj->value[11] = 0.0;
  obj->value[15] = 1.0;
  return obj;
}

CMatrix4* cmatrix4_setOrthogonalProjection(CMatrix4* obj, double right, double left, double top, double bottom, double far, double near) {
  obj->value[0] = 2.0/(right-left);
  obj->value[4] = 0.0;
  obj->value[8] = 0.0;
  obj->value[12] = -1*(right+left)/(right-left);

  obj->value[1] = 0.0;
  obj->value[5] = 2.0/(top-bottom);
  obj->value[9] = 0.0;
  obj->value[13] = -1*(top+bottom)/(top-bottom);

  obj->value[2] = 0.0;
  obj->value[6] = 0.0;
  obj->value[10] = -2/(far-near);
  obj->value[14] = -1*(far+near)/(far-near);

  obj->value[3] = 0.0;
  obj->value[7] = 0.0;
  obj->value[11] = 0.0;
  obj->value[15] = 1.0;
  return obj;
}

CMatrix4* cmatrix4_setPerspectiveProjection(CMatrix4* obj,
  double fovYRadians, double aspectRatio, double far, double near) {
  double h = tan(fovYRadians * 0.5);
  double w = h * aspectRatio;
  double n = near - far;

  obj->value[0] = 1.0/w;
  obj->value[4] = 0.0;
  obj->value[8] = 0.0;
  obj->value[12] = 0.0;

  obj->value[1] = 0.0;
  obj->value[5] = 1.0/h;
  obj->value[9] = 0.0;
  obj->value[13] = 0.0;

  obj->value[2] = 0.0;
  obj->value[6] = 0.0;
  obj->value[10] = (far + near) / n;
  obj->value[14] = (2.0 * near * far) / n;

  obj->value[3] = 0.0;
  obj->value[7] = 0.0;
  obj->value[11] = -1.0;
  obj->value[15] = 0.0;
  return obj;
}
/*
CMatrix4* cmatrix4_setPerspectiveProjection(CMatrix4* obj, double right, double left, double top, double bottom, double far, double near) {
  obj->value[0] = 2.0*near/(right-left);
  obj->value[4] = 0.0;
  obj->value[8] = (right+left)/(right-left);
  obj->value[12] = 0.0;

  obj->value[1] = 0.0;
  obj->value[5] = 2.0*near/(top-bottom);
  obj->value[9] = (top+bottom)/(top-bottom);
  obj->value[13] = 0.0;

  obj->value[2] = 0.0;
  obj->value[6] = 0.0;
  obj->value[10] = -1*(far+near)/(far-near);
  obj->value[14] = -2*(far*near)/(far-near);

  obj->value[3] = 0.0;
  obj->value[7] = 0.0;
  obj->value[11] = -1.0;
  obj->value[15] = 0.0;
  return obj;
}
*/
CMatrix4* cmatrix4_setLookAt(CMatrix4* obj,
  double posX, double posY, double posZ,
  double focusX, double focusY, double focusZ,
  double upDirectionX, double upDirectionY, double upDirectionZ
) {
  CVector3 pos;
  CVector3 focus;
  CVector3 upDirection;
  CVector3 z;
  CVector3 x;
  CVector3 y;
  initCVector3(&pos, posX, posY, posZ);
  initCVector3(&focus, focusX, focusY, focusZ);
  initCVector3(&upDirection, upDirectionX, upDirectionY, upDirectionZ);
  initCVector3(&z, 0.0, 0.0, 0.0);
  initCVector3(&x, 0.0, 0.0, 0.0);
  initCVector3(&y, 0.0, 0.0, 0.0);
  cvector3_sub(&pos, &focus, &z);
  cvector3_normalize(&z);
  cvector3_crossProduct(&upDirection, &z, &x);
  cvector3_normalize(&x);
  cvector3_crossProduct(&z, &x, &y);
  cvector3_normalize(&y);
  double rotatedEyeX = -1 * cvector3_dotProduct(&x, &pos);
  double rotatedEyeY = -1 * cvector3_dotProduct(&y, &pos);
  double rotatedEyeZ = -1 * cvector3_dotProduct(&z, &pos);
  cmatrix4_setValues(obj,
    x.value[0], x.value[1], x.value[2], rotatedEyeX,
    y.value[0], y.value[1], y.value[2], rotatedEyeY,
    z.value[0], z.value[1], z.value[2], rotatedEyeZ,
    0.0       , 0.0       , 0.0       , 1.0);
  return obj;
}
