#include "ccamera3d.h"
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
