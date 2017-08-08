#include "cmatrix4.h"
#include "cvector4.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void _freeVector4(void* tmp) {
  freeCObject(tmp);
}

CVector4* newCVector4(CMemory* cmemory) {
  CVector4 *ret = (CVector4*)cmemory_calloc(cmemory, 1, sizeof(CVector4));
  ret->parent.funcFree = _freeVector4;
  ret->parent.cmemory = cmemory;
  return ret;
}


CVector4* initCVector4(CVector4* obj, CMatrixValue v0, CMatrixValue v1, CMatrixValue v2, CMatrixValue v3) {
  initCObject((CObject*)obj, KVECTOR4_NAME);
  obj->value[0] = v0;
  obj->value[1] = v1;
  obj->value[2] = v2;
  obj->value[3] = v3;
  return obj;
}
