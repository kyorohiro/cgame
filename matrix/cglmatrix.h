
#ifndef __H_GL_MATRIX_
#define __H_GL_MATRIX_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cmatrix4.h"

CMatrix4* cmatrix4_setOrthogonalProjection(CMatrix4* obj, double right, double left, double top, double bottom, double far, double near);

CMatrix4* cmatrix4_setPerspectiveProjection(CMatrix4* obj,  double fovYRadians, double aspectRatio, double far, double near);

CMatrix4* cmatrix4_setLookAt(CMatrix4* obj,
  double posX, double posY, double posZ,
  double focusX, double focusY, double focusZ,
  double upDirectionX, double upDirectionY, double upDirectionZ
);

CMatrix4* cmatrix4_setLookAt2(CMatrix4* obj,
  double x, double y, double z,
  double rx, double ry, double rz,
  double sx, double sy, double sz
);

CMatrix4* cmatrix4_setRotationX(CMatrix4* obj, double radians);
CMatrix4* cmatrix4_setRotationY(CMatrix4* obj, double radians);
CMatrix4* cmatrix4_setRotationZ(CMatrix4* obj, double radians);
CMatrix4* cmatrix4_setTranslation(CMatrix4* obj, double x, double y, double z);
CMatrix4* cmatrix4_setScale(CMatrix4* obj, double x, double y, double z);

CVector4* cglmatrix4_unProject(
  double wx, double wy, double wz,
  CMatrix4* model, CMatrix4 * projection,
  double vx, double vy, double vw, double vh);
#endif
