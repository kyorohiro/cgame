#include "cray.h"
#include <stdio.h>

void _freeCRay(void* obj) {
  if(obj == NULL) {
    return;
  }
  CRay* rayObj = (CRay*)obj;
  releaseCObject((CObject*)rayObj->origin);
  releaseCObject((CObject*)rayObj->target);
  freeCObject(obj);
}

CRay* newCRay(CMemory* cmemory) {
  CRay* obj = cmemory_calloc(cmemory, 1, sizeof(CRay));
  ((CObject*)obj)->cmemory = cmemory;
  ((CObject*)obj)->funcFree = _freeCRay;
  return obj;
}

CRay* initCRay(CRay* obj,
  CMatrixValue originX, CMatrixValue originY, CMatrixValue originZ,
  CMatrixValue targetX, CMatrixValue targetY, CMatrixValue targetZ) {
    initCObject((CObject*)obj, KRAY_NAME);
    CMemory *cmemory = cobject_getCMemory((CObject*)obj);
    obj->origin = initCVector4(newCVector4(cmemory), originX, originY, originZ, 1.0);
    obj->target = initCVector4(newCVector4(cmemory), targetX, targetY, targetZ, 1.0);
    return obj;
}
