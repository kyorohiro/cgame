#ifndef __H_CMatrix4_Proj
#define __H_CMatrix4_Proj

#include "core/cobject.h"
#include "core/cmemory.h"
#include "vectorMath/cmatrix4.h"
#include "vectorMath/cvector3.h"
#include "vectorMath/cmatrix_trans.h"


CMatrix4* cmatrix4_setOrthogonalProjection(CMatrix4* obj, double right, double left, double top, double bottom, double far, double near);

CMatrix4* cmatrix4_setPerspectiveProjection(CMatrix4* obj,  double fovYRadians, double aspectRatio, double far, double near);

CMatrix4* cmatrix4_setFrustumProjection(CMatrix4* obj,
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
    CVMFloat viewportX,
    CVMFloat viewportWidth,
    CVMFloat viewportY,
    CVMFloat viewportHeight,
    CVMFloat pickX,
    CVMFloat pickY,
    CVMFloat pickZ,
    CVector3* out);
//
//
CMatrix4RawRef cmatrix4raw_setLookAt(CMatrix4RawRef obj,
  CMatrix4RawRef cameraPos, CMatrix4RawRef cameraFocus, CMatrix4RawRef upDirection);

int cmatrix4raw_unproject(
      CMatrix4Raw camera,
      CVMFloat viewportX,
      CVMFloat viewportWidth,
      CVMFloat viewportY,
      CVMFloat viewportHeight,
      CVMFloat pickX,
      CVMFloat pickY,
      CVMFloat pickZ,
      CVector3RawRef out);


#endif
