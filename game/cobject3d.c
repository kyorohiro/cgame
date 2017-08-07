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

void cobject3d_enterFrame(CObject3D* obj, CObject* cgame) {
  //  printf("cobject3d_enterFrame\r\n");
  if(obj->onEnterFrameFunc != NULL) {
    obj->onEnterFrameFunc((CObject*)obj, cgame);
  }
  if(obj->isLeaf == 1) {
    return;
  }
  for(int i=0;i<clinkedList_getLength(obj->nodes);i++) {
    cobject3d_enterFrame((CObject3D *)clinkedList_get(obj->nodes, i) , cgame);
  }
}


//
//
//
void freeCPrimitive3D(void* obj) {
  CPrimitive3D *objTmp = obj;
  if(objTmp->vertexs != NULL) {
    releaseCObject((CObject*)objTmp->vertexs);
  }
  freeCObject3D(obj);
}

CPrimitive3D* newCPrimitive3D(CMemory* mem) {
  CPrimitive3D * ret = cmemory_calloc(mem, 1, sizeof(CPrimitive3D));
  ret->parent.parent.cmemory = mem;
  ret->parent.parent.funcFree = freeCPrimitive3D;
  ret->parent.type = CObject3DTypePrimitive;
  return ret;
}

CPrimitive3D* initCPrimitive3D(CPrimitive3D* obj) {
  initCObject3D((CObject3D*)obj);
  return obj;
}

CPrimitive3D* initCPrimitive3DAsCube(CPrimitive3D* obj) {
  initCPrimitive3D(obj);
  float vVertices[] = {
    0.0f, 0.5f, 0.0f,    0.0, 0.0, 1.0, 1.0,  0.0, 0.0, 0.0,
   -0.5f, -0.5f, 0.0f,   0.0, 1.0, 0.0, 1.0,  0.0, 0.0, 0.0,
   0.5f, -0.5f, 0.0f,    1.0, 0.0, 0.0, 1.0,  0.0, 0.0, 0.0
  };
  obj->vertexs = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)vVertices, sizeof(CMatrixValue)*10*3);
  return obj;
}

CPrimitive3D* cprimitive3d_setRotate(CPrimitive3D* obj, double rx, double ry, double rz) {
  float* fVertexs = (float*)obj->vertexs->value;
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

CPrimitive3D* cprimitive3d_setPosition(CPrimitive3D* obj , double x, double y, double z) {
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


char* cprimitive3d_getVertexBinary(CPrimitive3D* obj) {
  if(obj->vertexs == NULL) {
    return NULL;
  }
  if(obj->status == 1) {
    //obj
    int length = cprimitive3d_getVertexBinaryLength(obj)/10;
    float *vVertices = (float*)obj->vertexs->value;
    for(int i=0;i<length;i++) {
      vVertices[i*10+7] = obj->rx;
      vVertices[i*10+8] = obj->ry;
      vVertices[i*10+9] = obj->rz;
    }
  }
  return obj->vertexs->value;

}

int cprimitive3d_getVertexBinaryLength(CPrimitive3D* obj) {
  if(obj->vertexs == NULL) {
    return 0;
  } else {
    return obj->vertexs->length/sizeof(CMatrixValue);
  }
}

/*
CMatrix4* cobject3d_getCMatrix4(CObject3D* obj) {
  cmatrix4_setIdentity(obj->mat);
  cmatrix4_outer(obj->mat, cmatrix4_setRotationX(obj->arg, obj->rx), obj->mat);
  cmatrix4_outer(obj->mat, cmatrix4_setRotationY(obj->arg, obj->ry), obj->mat);
  cmatrix4_outer(obj->mat, cmatrix4_setRotationZ(obj->arg, obj->rz), obj->mat);
  cmatrix4_outer(obj->mat, cmatrix4_setTranslation(obj->arg, obj->x, obj->y, obj->z), obj->mat);
  return obj->mat;
}
*/
