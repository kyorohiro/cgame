#include "cmatrix4.h"
#include "cvector3.h"
#include "cglmatrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


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

  obj->value[0] = 1.0/(h*aspectRatio);
  obj->value[4] = 0.0;
  obj->value[8] = 0.0;
  obj->value[12] = 0.0;

  obj->value[1] = 0.0;
  obj->value[5] = 1.0/h;
  obj->value[9] = 0.0;
  obj->value[13] = 0.0;
  obj->value[2] = 0.0;
  obj->value[6] = 0.0;
  obj->value[10] = -1*(far + near) / (far - near);
  obj->value[14] = -1*(2.0 * near * far) / (far - near);

  obj->value[3] = 0.0;
  obj->value[7] = 0.0;
  obj->value[11] = -1.0;
  obj->value[15] = 0.0;
  return obj;
}
CMatrix4* cmatrix4_setFrustumMatrix(CMatrix4* obj,
    double left, double right, double bottom, double top,
    double near, double far){
      obj->value[0] = (2.0*near)/(right-left);
      obj->value[4] = 0.0;
      obj->value[8] = (right+left)/(right-left);
      obj->value[12] = 0.0;

      obj->value[1] = 0.0;
      obj->value[5] = (2.0*near)/(top-bottom);
      obj->value[9] = (top + bottom) / (top-bottom);
      obj->value[13] = 0.0;

      obj->value[2] = 0.0;
      obj->value[6] = 0.0;
      obj->value[10] = -1*(far + near) / (far - near);
      obj->value[14] = -1*(2.0 * near * far) / (far - near);

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

CMatrix4* cmatrix4_setLookAt2(CMatrix4* obj,
  double x, double y, double z,
  double rx, double ry, double rz,
  double sx, double sy, double sz
) {
  CMatrix4 rotX;
  CMatrix4 rotY;
  CMatrix4 rotZ;
  CMatrix4 tran;
  CMatrix4 scal;
  CMatrix4 mat;
  cmatrix4_setIdentity(initCMatrix4(&mat));
  cmatrix4_mul(&mat, cmatrix4_setScale(initCMatrix4(&scal), sx, sy, sz), &mat);
  cmatrix4_mul(&mat, cmatrix4_setRotationX(initCMatrix4(&rotX), -rx), &mat);
  cmatrix4_mul(&mat, cmatrix4_setRotationY(initCMatrix4(&rotY), -ry), &mat);
  cmatrix4_mul(&mat, cmatrix4_setRotationZ(initCMatrix4(&rotZ), -rz), &mat);
  cmatrix4_mul(&mat, cmatrix4_setTranslation(initCMatrix4(&tran),  -x, -y, -z), obj);

  return obj;
}

CMatrix4* cmatrix4_setLookAt(CMatrix4* obj,
  double posX, double posY, double posZ,
  double focusX, double focusY, double focusZ,
  double upDirectionX, double upDirectionY, double upDirectionZ
) {
  CVector3Raw cameraPos; cameraPos[0] = posX; cameraPos[1] = posY; cameraPos[2] = posZ;
  CVector3Raw cameraFocus; cameraFocus[0] = focusX; cameraFocus[1] = focusY; cameraFocus[2] = focusZ;
  CVector3Raw upDirection; upDirection[0] = upDirectionX; upDirection[1] = upDirectionY; upDirection[2] = upDirectionZ;
  cmatrix4raw_setLookAt(obj->value, cameraPos, cameraFocus, upDirection);
  return obj;
}

CMatrix4RawRef cmatrix4raw_setLookAt(CMatrix4RawRef obj,
  CMatrix4RawRef cameraPos, CMatrix4RawRef cameraFocus, CMatrix4RawRef upDirection) {
  CVector3Raw z;
  CVector3Raw x;
  CVector3Raw y;

  cvector3raw_normalize(cvector3raw_sub(cameraPos, cameraFocus, z), z);
  cvector3raw_normalize(cvector3raw_crossProduct(upDirection, z, x), x);
  cvector3raw_normalize(cvector3raw_crossProduct(z, x, y), y);

  double rotatedEyeX = -1 * cvector3raw_dotProduct(x, cameraPos);
  double rotatedEyeY = -1 * cvector3raw_dotProduct(y, cameraPos);
  double rotatedEyeZ = -1 * cvector3raw_dotProduct(z, cameraPos);
  cmatrix4raw_setValues(obj,
    x[0], x[1], x[2], rotatedEyeX,
    y[0], y[1], y[2], rotatedEyeY,
    z[0], z[1], z[2], rotatedEyeZ,
    0.0 ,  0.0,  0.0, 1.0);
  return obj;
}

int cmatrix4_unproject(
    CMatrix4 *camera,
    CMatrixValueType viewportX,
    CMatrixValueType viewportWidth,
    CMatrixValueType viewportY,
    CMatrixValueType viewportHeight,
    CMatrixValueType pickX,
    CMatrixValueType pickY,
    CMatrixValueType pickZ,
    CVector3* out) {
  pickX = (pickX - viewportX);
  pickY = (pickY - viewportY);
  pickX = (2.0 * pickX / viewportWidth) - 1.0;
  pickY = (2.0 * pickY / viewportHeight) - 1.0;
  pickZ = (2.0 * pickZ) - 1.0;

  // Check if pick point is inside unit cube
  if (!(-1.0 <= pickX  && pickX <= 1.0 &&
      -1.0 <= pickY  && pickY <= 1.0 &&
      -1.0 <= pickZ  && pickZ <= 1.0)){
    return 0;
  }

  CMatrix4Raw invCamera;
  CMatrixValueType outDeterminant;
  cmatrix4raw_inverse(camera->value, invCamera, &outDeterminant);
  CMatrix4Raw tra;
  CVector4Raw v; v[0]=pickX; v[1]=pickY; v[2]=pickZ; v[3] = 1.0;
  cmatrix4raw_mulVector4Raw(invCamera, v, v);
  if(v[3] == 0.0) {
    return 0;
  }
  CMatrixValueType w = 1.0/v[3];
  out->value[0] = v[0] * w;
  out->value[1] = v[1] * w;
  out->value[2] = v[2] * w;
  return 1;
}

CVector4* cglmatrix4_unProject(
  double wx, double wy, double wz,
  CMatrix4* model, CMatrix4 * projection,
  double vx, double vy, double vw, double vh) {
    CMatrix4 *transform;
    if(model != NULL) {
      transform = cmatrix4_mul(projection , model, NULL);
    } else {
      transform = cmatrix4_setIdentity(initCMatrix4(newCMatrix4(getCMemory())));
      cmatrix4_mul(projection , model, transform);
    }
    CMatrixValueType out;
    cmatrix4_inverse(transform, transform, &out);
    CVector4 *inVector = initCVector4(newCVector4(getCMemory()),
      (wx - vx) / vw * 2.0 - 1.0,
      (wy - vy) / vh * 2.0 - 1.0,
      2.0 * wz - 1.0,
      1.0);
    cmatrix4_mulCVector4(transform, inVector, inVector);
    double v0 = inVector->value[0];
    double v1 = inVector->value[1];
    double v2 = inVector->value[2];
    double v3 = inVector->value[3];
    inVector->value[0] = v0 * v3;
    inVector->value[1] = v1 * v3;
    inVector->value[2] = v2 * v3;
    inVector->value[3] = 1.0;
    return inVector;
  }
