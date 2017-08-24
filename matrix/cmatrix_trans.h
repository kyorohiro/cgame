#ifndef __H_GL_MATRIX_TRANS_
#define __H_GL_MATRIX_TRANS_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cmatrix_inner.h"
#include "cmatrix4.h"
#include "cvector3.h"

CMatrix4* cmatrix4_setRotationX(CMatrix4* obj, double radians);
CMatrix4* cmatrix4_setRotationY(CMatrix4* obj, double radians);
CMatrix4* cmatrix4_setRotationZ(CMatrix4* obj, double radians);
CMatrix4* cmatrix4_setTranslation(CMatrix4* obj, double x, double y, double z);
CMatrix4* cmatrix4_setScale(CMatrix4* obj, double x, double y, double z);



CMatrix4RawRef cmatrix4raw_setRotationX(CMatrix4RawRef obj, double radians);
CMatrix4RawRef cmatrix4raw_setRotationY(CMatrix4RawRef obj, double radians);
CMatrix4RawRef cmatrix4raw_setRotationZ(CMatrix4RawRef obj, double radians);
CMatrix4RawRef cmatrix4raw_setTranslation(CMatrix4RawRef obj, double x, double y, double z);
CMatrix4RawRef cmatrix4raw_setScale(CMatrix4RawRef obj, double x, double y, double z);

#endif
