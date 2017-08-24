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
  cmatrix4raw_setRotationY(obj->value, radians);
  return obj;
}

// 1 0 0
// 0 c -s
// 0 s c
CMatrix4* cmatrix4_setRotationX(CMatrix4* obj, double radians){
  cmatrix4raw_setRotationX(obj->value, radians);
  return obj;
}

// 1 0 0
// 0 c -s
// 0 s c
CMatrix4* cmatrix4_setRotationZ(CMatrix4* obj, double radians){
  cmatrix4raw_setRotationZ(obj->value, radians);
  return obj;
}

CMatrix4* cmatrix4_setTranslation(CMatrix4* obj, double x, double y, double z) {
  cmatrix4raw_setTranslation(obj->value, x, y, z);
  return obj;
}

CMatrix4* cmatrix4_setScale(CMatrix4* obj, double x, double y, double z) {
  cmatrix4raw_setScale(obj->value, x, y, z);
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

//
//
//

CMatrix3RawRef cmatrix3raw_setRotationX(CMatrix3RawRef obj, double radians) {
  double c = cos(radians);
  double s = sin(radians);
  obj[0] = 1;
  obj[3] = 0.0;
  obj[6] = 0.0;

  obj[1] = 0.0;
  obj[4] = c;
  obj[7] = -s;

  obj[2] = 0.0;
  obj[5] =  s;
  obj[8] = c;
  return obj;
}

CMatrix3RawRef cmatrix3raw_setRotationY(CMatrix3RawRef obj, double radians) {
  double c = cos(radians);
  double s = sin(radians);
  obj[0] = c;
  obj[3] = 0.0;
  obj[6] = s;

  obj[1] = 0.0;
  obj[4] = 1.0;
  obj[7] = 0.0;

  obj[2] =  -s;
  obj[5] = 0.0;
  obj[8] = c;

  return obj;
}

CMatrix3RawRef cmatrix3raw_setRotationZ(CMatrix3RawRef obj, double radians) {
  double c = cos(radians);
  double s = sin(radians);
  obj[0] = c;
  obj[3] = -s;
  obj[6] = 0.0;

  obj[1] = s;
  obj[4] = c;
  obj[7] = 0.0;

  obj[2] = 0.0;
  obj[5] = 0.0;
  obj[8] = 1.0;

  return obj;
}


CMatrix4RawRef cmatrix3raw_setScale(CMatrix3RawRef obj, double x, double y, double z) {
  obj[0] = x;
  obj[3] = 0.0;
  obj[6] = 0.0;

  obj[1] = 0.0;
  obj[4] = y;
  obj[7] = 0.0;

  obj[2] = 0.0;
  obj[5] = 0.0;
  obj[8] = z;

  return obj;
}
