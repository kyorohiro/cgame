
#ifndef __H_GL_MATRIX_
#define __H_GL_MATRIX_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "matrix/cmatrix4.h"
#include "matrix/cvector3.h"
#include "matrix/cmatrix_trans.h"


CMatrix4* cmatrix4_setOrthogonalProjection(CMatrix4* obj, double right, double left, double top, double bottom, double far, double near);

CMatrix4* cmatrix4_setPerspectiveProjection(CMatrix4* obj,  double fovYRadians, double aspectRatio, double far, double near);

CMatrix4* cmatrix4_setFrustumMatrix(CMatrix4* obj,
    double left, double right, double bottom, double top,
    double near, double far);

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



int cmatrix4_unproject(
    CMatrix4 *camera,
    CMatrixValueType viewportX,
    CMatrixValueType viewportWidth,
    CMatrixValueType viewportY,
    CMatrixValueType viewportHeight,
    CMatrixValueType pickX,
    CMatrixValueType pickY,
    CMatrixValueType pickZ,
    CVector3* out);
//
//
CMatrix4RawRef cmatrix4raw_setLookAt(CMatrix4RawRef obj,
  CMatrix4RawRef cameraPos, CMatrix4RawRef cameraFocus, CMatrix4RawRef upDirection);

int cmatrix4raw_unproject(
      CMatrix4Raw camera,
      CMatrixValueType viewportX,
      CMatrixValueType viewportWidth,
      CMatrixValueType viewportY,
      CMatrixValueType viewportHeight,
      CMatrixValueType pickX,
      CMatrixValueType pickY,
      CMatrixValueType pickZ,
      CVector3RawRef out);



      /*
      CVector4* cglmatrix4_unProject(
        double wx, double wy, double wz,
        CMatrix4* model, CMatrix4 * projection,
        double vx, double vy, double vw, double vh);
      */
#endif
