#include "cobject3d.h"
#include "croot3d.h"
#include <stdio.h>

//
//
//
void freeCRoot3D(void* obj) {
  CRoot3D *objTmp = obj;
  freeCObject3D(obj);
}

CRoot3D* newCRoot3D(CMemory* mem) {
  CRoot3D * ret = cmemory_calloc(mem, 1, sizeof(CRoot3D));
  ret->parent.parent.cmemory = mem;
  ret->parent.parent.funcFree = freeCRoot3D;
  ret->parent.type = CObject3DTypePrimitive;
  return ret;
}

CRoot3D* initCRoot3D(CRoot3D* obj) {
  initCObject3D((CObject3D*)obj);
  return obj;
}
