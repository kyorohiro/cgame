#include "ccamera3d.h"
#include "cobject3d.h"
#include "core/cobject.h"
#include "vectorMath/cmatrix4.h"
#include <stdio.h>

void freeCCamera3D(void* obj) {
  CCamera3D* ret = (CCamera3D*)obj;
  releaseCObject((CObject*)ret->projection);
  releaseCObject((CObject*)ret->view);

  freeCObject3D(obj);
}

CCamera3D* newCCamera3D(CMemory* mem) {
  CCamera3D * ret = cmemory_calloc(mem, 1, sizeof(CCamera3D));
  ret->parent.parent.cmemory = mem;
  ret->parent.parent.funcFree = freeCCamera3D;
  ret->parent.type = CObject3DTypeCamera;
  ret->projection = cmatrix4_setIdentity(initCMatrix4(newCMatrix4(mem)));
  ret->view = cmatrix4_setIdentity(initCMatrix4(newCMatrix4(mem)));
  return ret;
}

CCamera3D* initCCamera3D(CCamera3D* obj) {
  initCObject3D((CObject3D*)obj);
  return obj;
}

CCamera3D* ccamera3d_updateAtPerspective(CCamera3D* obj,
  CMatrixVertexType x, CMatrixVertexType y, CMatrixVertexType z,
  CMatrixVertexType rx, CMatrixVertexType ry, CMatrixVertexType rz,
  CMatrixVertexType fovYRadians, CMatrixVertexType aspectRatio,
  CMatrixVertexType near, CMatrixVertexType far) {
  CObject3D* cobj = (CObject3D*)obj;
  CMatrix4* mat = cobj->mat;
  cmatrix4_setIdentity(mat);
  //

  printf("#proj %f %f %f : %f %f %f\r\n", x, y, z, rx, ry, rz);
  cmatrix4_setPerspectiveProjection(obj->projection, fovYRadians, aspectRatio, far, near);
  cmatrix4_show(obj->projection);

  printf("#view\r\n");
  cmatrix4_setLookAt2(obj->view, x, y, z, rx, ry, rz, 1.0, 1.0, 1.0);
  cmatrix4_show(obj->view);
  printf("\r\n");

  cmatrix4_mul(obj->projection, obj->view, mat);

  printf("\r\n");
  return obj;
}

CCamera3D* ccamera3d_update_setFrustumProjection(CCamera3D* obj,
    CMatrixVertexType x, CMatrixVertexType y, CMatrixVertexType z,
    CMatrixVertexType rx, CMatrixVertexType ry, CMatrixVertexType rz,
    CMatrixVertexType left, CMatrixVertexType right, CMatrixVertexType bottom, CMatrixVertexType top,
    CMatrixVertexType near, CMatrixVertexType far) {
      CObject3D* cobj = (CObject3D*)obj;
      CMatrix4* mat = cobj->mat;
      cmatrix4_setIdentity(mat);
      //

      cmatrix4_setFrustumProjection(obj->projection, left, right, bottom, top, near, far);
      cmatrix4_setLookAt2(obj->view, x, y, z, rx, ry, rz, 1.0, 1.0, 1.0);
      cmatrix4_mul(obj->projection, obj->view, mat);

      printf("#proj %f %f %f : %f %f %f\r\n", x, y, z, rx, ry, rz);

      cmatrix4_show(obj->projection);
      printf("\r\n");
      printf("#view\r\n");
      cmatrix4_show(obj->view);
      printf("\r\n");

      return obj;
}
