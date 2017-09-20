#ifndef __H_CMatrix4_Trans
#define __H_CMatrix4_Trans

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvectorMath_inner.h"
#include "cmatrix4.h"
#include "cmatrix3.h"
#include "cvector3.h"

CMatrix4* cmatrix4_setRotationX(CMatrix4* obj, double radians);
CMatrix4* cmatrix4_setRotationY(CMatrix4* obj, double radians);
CMatrix4* cmatrix4_setRotationZ(CMatrix4* obj, double radians);
CMatrix4* cmatrix4_setTranslation(CMatrix4* obj, double x, double y, double z);
CMatrix4* cmatrix4_setScale(CMatrix4* obj, double x, double y, double z);
CMatrix4* cmatrix4_setXyxRXyzSXyz(CMatrix4* obj,
              CVMFloat centerX, CVMFloat centerY, CVMFloat centerZ,
              CVMFloat x, CVMFloat y, CVMFloat z,
              CVMFloat rx, CVMFloat ry, CVMFloat rz,
              CVMFloat sx, CVMFloat sy, CVMFloat sz);

CMatrix3* cmatrix3_setRotationX(CMatrix3* obj, double radians);
CMatrix3* cmatrix3_setRotationY(CMatrix3* obj, double radians);
CMatrix3* cmatrix3_setRotationZ(CMatrix3* obj, double radians);
CMatrix3* cmatrix3_setScale(CMatrix3* obj, double x, double y, double z);


CMatrix4RawRef cmatrix4raw_setRotationX(CMatrix4RawRef obj, double radians);
CMatrix4RawRef cmatrix4raw_setRotationY(CMatrix4RawRef obj, double radians);
CMatrix4RawRef cmatrix4raw_setRotationZ(CMatrix4RawRef obj, double radians);
CMatrix4RawRef cmatrix4raw_setTranslation(CMatrix4RawRef obj, double x, double y, double z);
CMatrix4RawRef cmatrix4raw_setScale(CMatrix4RawRef obj, double x, double y, double z);


CMatrix3RawRef cmatrix3raw_setRotationX(CMatrix3RawRef obj, double radians);
CMatrix3RawRef cmatrix3raw_setRotationY(CMatrix3RawRef obj, double radians);
CMatrix3RawRef cmatrix3raw_setRotationZ(CMatrix3RawRef obj, double radians);
CMatrix3RawRef cmatrix3raw_setScale(CMatrix3RawRef obj, double x, double y, double z);
#endif
