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
  CMemory *mem = cobject_getCMemory((CObject*)obj);
  initCObject3D((CObject3D*)obj);
  obj->matrixList = initCArrayList(newCArrayList(cobject_getCMemory((CObject*)obj)), depth+1);
  carrayList_openAll(obj->matrixList);
  carrayList_set(obj->matrixList, 0, cobject_downCounter(
    (CObject*)cmatrix4_setIdentity(initCMatrix4(newCMatrix4(mem)))
  ));

  return obj;
}

CRoot3D* croot3d_pushMulMatrix(CRoot3D* obj, CMatrix4 *mat) {

  CMatrix4* mat1 = (CMatrix4*)carrayList_get(obj->matrixList, obj->index);
  CMatrix4* mat2 = cmatrix4_mul(mat1, mat, NULL);

  carrayList_set(obj->matrixList, ++obj->index, cobject_downCounter((CObject*)mat2));

  return obj;
}

CMatrix4* croot3d_popMulMatrix(CRoot3D* obj) {
  CMatrix4* mat1 = (CMatrix4*)carrayList_get(obj->matrixList, obj->index);
  obj->index--;
  return mat1;
}

CMatrix4* croot3d_peekMulMatrix(CRoot3D* obj) {
  return (CMatrix4*)carrayList_get(obj->matrixList, obj->index);
}
