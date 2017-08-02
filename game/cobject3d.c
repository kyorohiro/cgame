#include "cobject3d.h"
#include <stdio.h>

void _freeCObject3D(void* obj);

//
CObject3D* newCObject3D(CMemory* mem) {
  CObject3D * ret = cmemory_calloc(mem, 1, sizeof(CObject3D));
  ret->parent.cmemory = mem;
  return ret;
}
//char* title, int width, int height
CObject3D* initCObject3D(CObject3D* obj) {
  initCObject((CObject*)obj, OBJECT3D_NAME);
  obj->parent.funcFree = _freeCObject3D;
  obj->mat = kmatrix_setIdentity(initKMatrix(newKMatrix()));
  obj->arg = kmatrix_setIdentity(initKMatrix(newKMatrix()));
  return obj;
}

CObject3D* cobject3d_setRotate(CObject3D* obj, double rx, double ry, double rz) {
  if(obj->rx != rx) {
    obj->rx = rx;
    obj->status = 1;
  }
  if(obj->ry != ry) {
    obj->ry = ry;
    obj->status = 1;
  }
  if(obj->rz != rz) {
    obj->rz = rz;
    obj->status = 1;
  }
  return obj;
}

CObject3D* cobject3d_setPosition(CObject3D* obj , double x, double y, double z) {
  if(obj->x != x) {
    obj->x = x;
    obj->status = 1;
  }
  if(obj->y != y) {
    obj->y = y;
    obj->status = 1;
  }
  if(obj->z != z) {
    obj->z = z;
    obj->status = 1;
  }
  return obj;
}

KMatrix* cobject3d_getKMatrix(CObject3D* obj) {
  kmatrix_setIdentity(obj->mat);
  kmatrix_outer(obj->mat, kmatrix_setRotationX(obj->arg, obj->rx), obj->mat);
  kmatrix_outer(obj->mat, kmatrix_setRotationY(obj->arg, obj->ry), obj->mat);
  kmatrix_outer(obj->mat, kmatrix_setRotationZ(obj->arg, obj->rz), obj->mat);
  kmatrix_outer(obj->mat, kmatrix_setTranslation(obj->arg, obj->x, obj->y, obj->z), obj->mat);
  return obj->mat;
}
