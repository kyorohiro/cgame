#include "cobject3d.h"
#include "cprimitive3d.h"
#include <stdio.h>

//
//
//
void freeCPrimitive3D(void* obj) {
  CPrimitive3D *objTmp = obj;
  if(objTmp->vertexSet != NULL) {
    releaseCObject((CObject*)objTmp->vertexSet);
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
  obj->ca =obj->cb = obj->cg = obj->cr = 1.0;
  obj->vetexUnitSize = 13;
  return obj;
}

CPrimitive3D* cprimitive3d_setColor(CPrimitive3D* obj, double a, double r, double g, double b) {
  obj->ca = a;
  obj->cr = r;
  obj->cg = g;
  obj->cb = b;
  obj->status = 1;
  return obj;
}

char* cprimitive3d_getVertexSetBinary(CPrimitive3D* obj) {
  if(obj->vertexSet == NULL) {
    return NULL;
  }

  if(obj->status == 1)
  {
    //obj
    int length = cprimitive3d_getVertexSetBinaryLength(obj)/obj->vetexUnitSize;
    float *vVertices = (float*)obj->vertexSet->value;
    for(int i=0;i<length;i++) {
      //
      vVertices[i*obj->vetexUnitSize+3] = obj->cr;
      vVertices[i*obj->vetexUnitSize+4] = obj->cg;
      vVertices[i*obj->vetexUnitSize+5] = obj->cb;
      vVertices[i*obj->vetexUnitSize+6] = obj->ca;
    }
  }
  return obj->vertexSet->value;

}

int cprimitive3d_getVertexSetBinaryLength(CPrimitive3D* obj) {
  if(obj->vertexSet == NULL) {
    return 0;
  } else {
    return obj->vertexSet->length;
  }
}

char* cprimitive3d_getIndexBinary(CPrimitive3D* obj) {
  if(obj->indexes == NULL) {
    return 0;
  } else {
    return obj->indexes->value;
  }
}

int cprimitive3d_getIndexBinaryLength(CPrimitive3D* obj) {
  if(obj->indexes == NULL) {
    return 0;
  } else {
    return obj->indexes->length;
  }
}


char* cprimitive3d_getVertexBinary(CPrimitive3D* obj) {
  return obj->vertexes->value;
}

int cprimitive3d_getVertexBinaryLength(CPrimitive3D* obj) {
  if(obj->vertexes == NULL) {
    return 0;
  } else {
    return obj->vertexes->length;
  }
}

char* cprimitive3d_getNormalBinary(CPrimitive3D* obj) {
  return obj->normals->value;
}

int cprimitive3d_getNormalBinaryLength(CPrimitive3D* obj) {
  if(obj->normals == NULL) {
    return 0;
  } else {
    return obj->normals->length;
  }
}

char* cprimitive3d_getColorBinary(CPrimitive3D* obj) {
  return obj->colors->value;
}

int cprimitive3d_getColorBinaryLength(CPrimitive3D* obj) {
  if(obj->colors == NULL) {
    return 0;
  } else {
    return obj->colors->length;
  }
}
