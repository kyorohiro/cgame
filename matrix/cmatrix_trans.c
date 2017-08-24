#include "cmatrix4.h"
#include "cvector3.h"
#include "cmatrix_trans.h"
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

  obj->value[1] = 0.0;
  obj->value[5] = y;
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


CMatrix4RawRef cmatrix4raw_setRotationX(CMatrix4RawRef obj, double radians) {
  double c = cos(radians);
  double s = sin(radians);
  obj[0] = 1;
  obj[4] = 0.0;
  obj[8] = 0.0;
  obj[12] = 0.0;

  obj[1] = 0.0;
  obj[5] = c;
  obj[9] = -s;
  obj[13] = 0.0;

  obj[2] = 0.0;
  obj[6] =  s;
  obj[10] = c;
  obj[14] = 0.0;

  obj[3] = 0.0;
  obj[7] = 0.0;
  obj[11] = 0.0;
  obj[15] = 1.0;
  return obj;
}

CMatrix4RawRef cmatrix4raw_setRotationY(CMatrix4RawRef obj, double radians) {
  double c = cos(radians);
  double s = sin(radians);
  obj[0] = c;
  obj[4] = 0.0;
  obj[8] = s;
  obj[12] = 0.0;

  obj[1] = 0.0;
  obj[5] = 1.0;
  obj[9] = 0.0;
  obj[13] = 0.0;

  obj[2] =  -s;
  obj[6] = 0.0;
  obj[10] = c;
  obj[14] = 0.0;

  obj[3] = 0.0;
  obj[7] = 0.0;
  obj[11] = 0.0;
  obj[15] = 1.0;

  return obj;
}

CMatrix4RawRef cmatrix4raw_setRotationZ(CMatrix4RawRef obj, double radians) {
  double c = cos(radians);
  double s = sin(radians);
  obj[0] = c;
  obj[4] = -s;
  obj[8] = 0.0;
  obj[12] = 0.0;

  obj[1] = s;
  obj[5] = c;
  obj[9] = 0.0;
  obj[13] = 0.0;

  obj[2] = 0.0;
  obj[6] = 0.0;
  obj[10] = 1.0;
  obj[14] = 0.0;

  obj[3] = 0.0;
  obj[7] = 0.0;
  obj[11] = 0.0;
  obj[15] = 1.0;
  return obj;
}

CMatrix4RawRef cmatrix4raw_setTranslation(CMatrix4RawRef obj, double x, double y, double z) {
  obj[0] = 1.0;
  obj[4] = 0.0;
  obj[8] = 0.0;
  obj[12] = x;

  obj[1] = 0.0;
  obj[5] = 1.0;
  obj[9] = 0.0;
  obj[13] = y;

  obj[2] = 0.0;
  obj[6] = 0.0;
  obj[10] = 1.0;
  obj[14] = z;

  obj[3] = 0.0;
  obj[7] = 0.0;
  obj[11] = 0.0;
  obj[15] = 1.0;
  return obj;
}

CMatrix4RawRef cmatrix4raw_setScale(CMatrix4RawRef obj, double x, double y, double z) {
  obj[0] = x;
  obj[4] = 0.0;
  obj[8] = 0.0;
  obj[12] = 0.0;

  obj[1] = 0.0;
  obj[5] = y;
  obj[9] = 0.0;
  obj[13] = 0.0;

  obj[2] = 0.0;
  obj[6] = 0.0;
  obj[10] = z;
  obj[14] = 0.0;

  obj[3] = 0.0;
  obj[7] = 0.0;
  obj[11] = 0.0;
  obj[15] = 1.0;
  return obj;
}
