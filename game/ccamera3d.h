#ifndef _H_3DCAMERA
#define _H_3DCAMERA


#include "core/cobject.h"
#include "core/cmemory.h"
#include "matrix/cmatrix4.h"
#include "core/cbytes.h"
#include "core/clinkedList.h"
#include "matrix/cmatrix4.h"
#include "cobject3d.h"
#define CAMERA3D_NAME "ca3"

//
//
typedef struct {
  CObject3D parent;
  CMatrix4 *view;
  CMatrix4 *projection;
} CCamera3D;

CCamera3D* newCCamera3D(CMemory* mem);
CCamera3D* initCCamera3D(CCamera3D*);
CCamera3D* ccamera3d_update(CCamera3D* obj,
  CMatrixVertexType x, CMatrixVertexType y, CMatrixVertexType z,
  CMatrixVertexType rx, CMatrixVertexType ry, CMatrixVertexType rz,
  CMatrixVertexType fovYRadians, CMatrixVertexType aspect,
  CMatrixVertexType near, CMatrixVertexType far);
#endif
