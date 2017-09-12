#include "cobject3d.h"
#include "cprimitive3d.h"
#include <stdio.h>

//
//
//
void freeCPrimitive3D(void* obj) {
  CPrimitive3D *objTmp = obj;
  if(objTmp->vertexes != NULL) {
    releaseCObject((CObject*)objTmp->vertexes);
  }
  if(objTmp->colors != NULL) {
    releaseCObject((CObject*)objTmp->colors);
  }
  if(objTmp->colors != NULL) {
    releaseCObject((CObject*)objTmp->normals);
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

CPrimitive3D* cprimitive3d_setColor(CPrimitive3D* obj, double a, double r, double g, double b) {
  int colorLen = cbytes_getLength((CBytes*)obj->colors)/sizeof(CMatrixVertexType);
  CMatrixVertexType* colors = (CMatrixVertexType*)obj->colors->value;
  for(int i=0; i<colorLen;i+=4) {
    colors[i+0] = r;
    colors[i+1] = g;
    colors[i+2] = b;
    colors[i+3] = a;
  }
  return obj;
}


//
//
//
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

//
CImage* cprimitive3d_getCImage(CPrimitive3D* obj) {
  return obj->image;
}

void cprimitive3d_setCImage(CPrimitive3D* obj, CImage* img) {
  obj->image = img;
}

char* cprimitive3d_getTextCoordBinary(CPrimitive3D* obj) {
  if(obj->texCoords == NULL) {
    return NULL;
  } else {
    return obj->texCoords->value;
  }
}

int cprimitive3d_getTextCoordBinaryLength(CPrimitive3D* obj) {
  if(obj->texCoords == NULL) {
    return 0;
  } else {
    return obj->texCoords->length;
  }
}
