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
//  obj->parent.funcFree = freeCObject3D;
  obj->mat = cmatrix4_setIdentity(initCMatrix4(newCMatrix4(obj->parent.cmemory)));
  obj->arg = cmatrix4_setIdentity(initCMatrix4(newCMatrix4(obj->parent.cmemory)));
  return obj;
}

CMatrix4* cobject3d_getCMatrix4(CObject3D* obj) {
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



  if(objTmp->nodes != NULL) {
    releaseCObject((CObject*)objTmp->nodes);
  }

  freeCObject(obj);
}


CLinkedList* cobject3d_getNodes(CObject3D* obj) {
  return obj->nodes;
}

void cobject3d_enterFrame(CObject3D* obj, CObject3D* root, CObject* cgame) {
  //  printf("cobject3d_enterFrame\r\n");
  if(obj->onEnterFrameFunc != NULL) {
    obj->onEnterFrameFunc((CObject*)obj, cgame);
  }
  if(obj->isLeaf == 1) {
    return;
  }
  for(int i=0;i<clinkedList_getLength(obj->nodes);i++) {
    cobject3d_enterFrame((CObject3D *)clinkedList_get(obj->nodes, i), root, cgame);
  }
}



/*
CMatrix4* cobject3d_getCMatrix4(CObject3D* obj) {
  cmatrix4_setIdentity(obj->mat);
  cmatrix4_multiply(obj->mat, cmatrix4_setRotationX(obj->arg, obj->rx), obj->mat);
  cmatrix4_multiply(obj->mat, cmatrix4_setRotationY(obj->arg, obj->ry), obj->mat);
  cmatrix4_multiply(obj->mat, cmatrix4_setRotationZ(obj->arg, obj->rz), obj->mat);
  cmatrix4_multiply(obj->mat, cmatrix4_setTranslation(obj->arg, obj->x, obj->y, obj->z), obj->mat);
  return obj->mat;
}
*/
