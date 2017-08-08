#include "cobject3d.h"
#include "cprimitive3d.h"
#include <stdio.h>

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

CPrimitive3D* initCPrimitive3DAsTriangle(CPrimitive3D* obj) {
  initCPrimitive3D(obj);
  float vVertices[] = {
    0.0f, 0.5f, 0.0f,    0.0, 0.0, 1.0, 1.0,  0.0, 0.0, 0.0,
   -0.5f, -0.5f, 0.0f,   0.0, 1.0, 0.0, 1.0,  0.0, 0.0, 0.0,
   0.5f, -0.5f, 0.0f,    1.0, 0.0, 0.0, 1.0,  0.0, 0.0, 0.0
  };
  obj->vertexs = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)vVertices, sizeof(CMatrixValue)*10*3);
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
