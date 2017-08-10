#include "ccamera3d.h"
#include "cobject3d.h"
#include "matrix/cmatrix4.h"
#include <stdio.h>

void freeCCamera3D(void* obj) {
  freeCObject3D(obj);
}

CCamera3D* newCCamera3D(CMemory* mem) {
  CCamera3D * ret = cmemory_calloc(mem, 1, sizeof(CCamera3D));
  ret->parent.parent.cmemory = mem;
  ret->parent.parent.funcFree = freeCCamera3D;
  ret->parent.type = CObject3DTypeCamera;
  return ret;
}

CCamera3D* initCCamera3D(CCamera3D* obj) {
  initCObject3D((CObject3D*)obj);
  return obj;
}

CCamera3D* ccamera3d_update(CCamera3D* obj,
  CMatrixValue x, CMatrixValue y, CMatrixValue z,
  CMatrixValue rx, CMatrixValue ry, CMatrixValue rz,
  CMatrixValue fovYRadians, CMatrixValue aspectRatio,
  CMatrixValue near, CMatrixValue far) {
  CObject3D* cobj = (CObject3D*)obj;
  CMatrix4* mat = cobj->mat;
  cmatrix4_setIdentity(mat);
  //
  CMatrix4 rot;
  CMatrix4 rotX;
  CMatrix4 rotY;
  CMatrix4 rotZ;
  cmatrix4_setIdentity(initCMatrix4(&rot));
  cmatrix4_multiply(&rot, cmatrix4_setRotationX(initCMatrix4(&rotX), rx), &rot);
  cmatrix4_multiply(&rot, cmatrix4_setRotationY(initCMatrix4(&rotY), ry), &rot);
  cmatrix4_multiply(&rot, cmatrix4_setRotationZ(initCMatrix4(&rotZ), rz), &rot);

  CVector4 defF;
  CVector4 defD;
  initCVector4(&defF, 0.0, 1.0, 0.0, 1.0);
  initCVector4(&defD, 0.0, 0.0, -1.0, 1.0);

  cmatrix4_multiplyCVector4(&rot, &defF, &defF);
  cmatrix4_multiplyCVector4(&rot, &defD, &defD);
  cmatrix4_setPerspectiveProjection(mat, fovYRadians, aspectRatio, far, near);

  CMatrix4 view;
  initCMatrix4(&view);
  cmatrix4_setLookAt(&view, x, y, z,
    defF.value[0], defF.value[1], defF.value[2],
    defD.value[0], defD.value[1], defD.value[2]);

  return obj;
}
