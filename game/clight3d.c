#include "clight3d.h"
#include "cobject3d.h"
#include "vectorMath/cmatrix4.h"
#include <stdio.h>

void freeCLight3D(void* obj) {
  freeCObject3D(obj);
}


CLight3D* newCLight3D(CMemory* mem) {
  CLight3D * ret = cmemory_calloc(mem, 1, sizeof(CLight3D));
  ret->parent.parent.cmemory = mem;
  ret->parent.parent.funcFree = freeCLight3D;
  ret->parent.type = CObject3DTypeLight;
  return ret;
}

CLight3D* initCLight3D(CLight3D* obj) {
  return (CLight3D*)initCObject3D((CObject3D*)obj);
}
