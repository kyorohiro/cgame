#include "cmatrix4.h"
#include "cvector3.h"
#include "cmatrix_proj.h"
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

CMatrix4* cmatrix4_setFrustumProjection(CMatrix4* obj,
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

CMatrix4* cmatrix4_setLookAt2(CMatrix4* obj,
  double x, double y, double z,
  double rx, double ry, double rz,
  double sx, double sy, double sz
) {
  CMatrix4Raw rotX;
  CMatrix4Raw rotY;
  CMatrix4Raw rotZ;
  CMatrix4Raw tran;
  CMatrix4Raw scal;
  CMatrix4Raw mat;
  cmatrix4raw_setIdentity(mat);
  cmatrix4raw_mul(mat, cmatrix4raw_setScale(scal, sx, sy, sz), mat);
  cmatrix4raw_mul(mat, cmatrix4raw_setRotationX(rotX, -rx), mat);
  cmatrix4raw_mul(mat, cmatrix4raw_setRotationY(rotY, -ry), mat);
  cmatrix4raw_mul(mat, cmatrix4raw_setRotationZ(rotZ, -rz), mat);
  cmatrix4raw_mul(mat, cmatrix4raw_setTranslation(tran,  -x, -y, -z), obj->value);

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
    CVMFloat viewportX,
    CVMFloat viewportWidth,
    CVMFloat viewportY,
    CVMFloat viewportHeight,
    CVMFloat pickX,
    CVMFloat pickY,
    CVMFloat pickZ,
    CVector3* out) {
  if(out ==NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)camera);
    out = initCVector3(newCVector3(memory), 0.0, 0.0, 0.0);
  }
  return cmatrix4raw_unproject(camera->value, viewportX, viewportWidth, viewportY, viewportHeight,
     pickX, pickY, pickZ, out->value);
}


int cmatrix4raw_unproject(
      CMatrix4RawRef camera,
      CVMFloat viewportX,
      CVMFloat viewportWidth,
      CVMFloat viewportY,
      CVMFloat viewportHeight,
      CVMFloat pickX,
      CVMFloat pickY,
      CVMFloat pickZ,
      CVector3RawRef out) {
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
  //printf(">> >> %f %f %f\r\n", pickX, pickY, pickZ);
  CMatrix4Raw invCamera;
  CVMFloat outDeterminant;
  cmatrix4raw_inverse(camera, invCamera, &outDeterminant);
  CMatrix4Raw tra;
  CVector4Raw v; v[0]=pickX; v[1]=pickY; v[2]=pickZ; v[3] = 1.0;
  cmatrix4raw_mulVector4Raw(invCamera, v, v);
  if(v[3] == 0.0) {
    return 0;
  }
  CVMFloat w = 1.0/v[3];
  out[0] = v[0] * w;
  out[1] = v[1] * w;
  out[2] = v[2] * w;
  return 1;
}
