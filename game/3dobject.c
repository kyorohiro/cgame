#include "3dobject.h"
#include <stdio.h>

void _freeObject3D(void* obj);

//
Object3D* newObject3D(CMemory* mem) {
  Object3D * ret = cmemory_calloc(mem, 1, sizeof(Object3D));
  ret->parent.cmemory = mem;
  return ret;
}
//char* title, int width, int height
Object3D* initObject3D(Object3D* obj) {
  initCObject((CObject*)obj, OBJECT3D_NAME);
  obj->parent.funcFree = _freeObject3D;
  obj->mat = kmatrix_setIdentity(initKMatrix(newKMatrix()));
  return obj;
}

Object3D* object3d_setRotate(Object3D* obj, double rx, double ry, double rz) {
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

Object3D* object3d_setPosition(Object3D* obj , double x, double y, double z) {
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

KMatrix* object3d_getKMatrix(Object3D* obj) {
  return obj->mat;
}
