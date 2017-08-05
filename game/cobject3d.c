#include "cobject3d.h"
#include <stdio.h>



//
CObject3D* newCObject3D(CMemory* mem) {
  CObject3D * ret = cmemory_calloc(mem, 1, sizeof(CObject3D));
  ret->parent.cmemory = mem;
  ret->parent.funcFree = freeCObject3D;
  return ret;
}

//char* title, int width, int height
CObject3D* initCObject3D(CObject3D* obj) {
  initCObject((CObject*)obj, OBJECT3D_NAME);
  obj->parent.funcFree = freeCObject3D;
  obj->mat = cmatrix4_setIdentity(initCMatrix4(newCMatrix4(obj->parent.cmemory)));
  obj->arg = cmatrix4_setIdentity(initCMatrix4(newCMatrix4(obj->parent.cmemory)));
  return obj;
}

CObject3D* initCObject3DAsCube(CObject3D* obj) {
  initCObject3D(obj);
  float vVertices[] = {
    0.0f, 0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f};
  obj->vertexs = initCBytes(newCBytes(obj->parent.cmemory), (char*)vVertices, 2*9);
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

CMatrix4* cobject3d_getCMatrix4(CObject3D* obj) {
  cmatrix4_setIdentity(obj->mat);
  cmatrix4_outer(obj->mat, cmatrix4_setRotationX(obj->arg, obj->rx), obj->mat);
  cmatrix4_outer(obj->mat, cmatrix4_setRotationY(obj->arg, obj->ry), obj->mat);
  cmatrix4_outer(obj->mat, cmatrix4_setRotationZ(obj->arg, obj->rz), obj->mat);
  cmatrix4_outer(obj->mat, cmatrix4_setTranslation(obj->arg, obj->x, obj->y, obj->z), obj->mat);
  return obj->mat;
}

CObject3D* cobject3d_addNode(CObject3D* obj, CObject3D* node) {
  if(obj->nodes == NULL) {
    obj->nodes = initCLinkedList(newCLinkedList(obj->parent.cmemory));
  }
  clinkedList_addLast(obj->nodes, (CObject*)node);
  return obj;
}

void freeCObject3D(void* obj) {
  CObject3D *objTmp = obj;
  releaseCObject((CObject*)objTmp->arg);
  releaseCObject((CObject*)objTmp->mat);

  if(objTmp->vertexs != NULL) {
    releaseCObject((CObject*)objTmp->vertexs);
  }

  if(objTmp->nodes != NULL) {
    releaseCObject((CObject*)objTmp->nodes);
  }

  freeCObject(obj);
}
