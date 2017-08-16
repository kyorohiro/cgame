#include "cobject3d.h"
#include "croot3d.h"
#include <stdio.h>

//
//
//
void freeCRoot3D(void* obj) {
  CRoot3D *objTmp = obj;
  releaseCObject((CObject*)objTmp->matrixList);
  freeCObject3D(obj);
}

CRoot3D* newCRoot3D(CMemory* mem) {
  CRoot3D * ret = cmemory_calloc(mem, 1, sizeof(CRoot3D));
  ret->parent.parent.cmemory = mem;
  ret->parent.parent.funcFree = freeCRoot3D;
  ret->parent.type = CObject3DTypeRoot;
  ret->parent.parent.funcFree = freeCRoot3D;
  return ret;
}

CRoot3D* initCRoot3D(CRoot3D* obj, int depth) {
  initCObject3D((CObject3D*)obj);
  obj->matrixList = initCArrayList(newCArrayList(cobject_getCMemory((CObject*)obj)), depth+1);
  return obj;
}

CRoot3D* croot3d_pushMulMatrix(CRoot3D* obj, CMatrix4 *mat) {
  return obj;
}
