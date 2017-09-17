#include "csprite2d.h"
#include <stdio.h>

void freeCSprite2D(void* obj) {
  CSprite2D* objTmp = obj;
  freeCObject3D(obj);
}

CSprite2D* newCSprite2D(CMemory* mem) {
  CSprite2D* ret = cmemory_calloc(mem, 1, sizeof(CSprite2D));
  ret->parent.parent.cmemory = mem;
  ret->parent.parent.funcFree = freeCSprite2D;
  return ret;
}

CSprite2D* initCSprite2D(CSprite2D* obj, int width, int height) {
  initCPrimitive3D((CPrimitive3D*)obj);
  return obj;
}

CSprite2D* createCSprite2D(int width, int height) {
  return initCSprite2D(newCSprite2D(getCMemory()), width, height);
}

CSprite2D* csprite2d_setXYZ(CSprite2D* obj, CMatrixVertexType x, CMatrixVertexType y, CMatrixVertexType z) {
  obj->x = x;
  obj->y = y;
  obj->z = z;
  return obj;
}

CSprite2D* csprite2d_setRXYZ(CSprite2D* obj, CMatrixVertexType rx, CMatrixVertexType ry, CMatrixVertexType rz) {
  obj->rx = rx;
  obj->ry = ry;
  obj->rz = rz;
  return obj;
}

CSprite2D* csprite2d_update(CSprite2D* obj) {
  CObject3D* obj3d = (CObject3D*)obj;
  CMatrix4Raw center;
  CMatrix4Raw centerB;
  CMatrix4Raw move;

  CMatrix4Raw rotateX;
  CMatrix4Raw rotateY;
  CMatrix4Raw rotateZ;
  cmatrix4raw_setTranslation(center, obj3d->centerX, obj3d->centerY, obj3d->centerZ);
  cmatrix4raw_setRotationX(rotateX, obj->rx);
  cmatrix4raw_setRotationY(rotateX, obj->ry);
  cmatrix4raw_setRotationZ(rotateX, obj->rz);
  cmatrix4raw_setTranslation(centerB, obj3d->centerX, obj3d->centerY, obj3d->centerZ);
  cmatrix4raw_setTranslation(move, obj->x, obj->y, obj->z);

  CMatrix4* mat = obj3d->mat;
  cmatrix4raw_mul(center, mat->value, mat->value);
  cmatrix4raw_mul(rotateX, mat->value, mat->value);
  cmatrix4raw_mul(rotateY, mat->value, mat->value);
  cmatrix4raw_mul(rotateZ, mat->value, mat->value);
  cmatrix4raw_mul(centerB, mat->value, mat->value);
  cmatrix4raw_mul(move, mat->value, mat->value);

  return obj;
}
