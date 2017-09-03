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

CPrimitive3D* initCPrimitive3DAsTriangle(CPrimitive3D* obj) {
  initCPrimitive3D(obj);
  CMatrixVertexType vVerticesSet[] = {
    0.0f, 0.5f, 0.0f,    0.0, 0.0, 1.0, 1.0,  0.0, 0.0, 0.0,
   -0.5f, -0.5f, 0.0f,   0.0, 1.0, 0.0, 1.0,  0.0, 0.0, 0.0,
   0.5f, -0.5f, 0.0f,    1.0, 0.0, 0.0, 1.0,  0.0, 0.0, 0.0
  };
  CMatrixVertexType vertices[] = {
    0.0f, 0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
  };
  CMatrixVertexType normals[] = {
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0
  };
  CMatrixVertexType colors[] = {
     0.0, 0.0, 0.0,
     0.0, 0.0, 0.0,
     0.0, 0.0, 0.0
  };
  CMatrixIndexType indexes[] = {
    0, 1, 2
  };
  obj->vertexSet = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)vVerticesSet, sizeof(CMatrixVertexType)*PRIMITIVE3D_BUFFER_SIZE*3);
  obj->indexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)indexes, sizeof(indexes));
  obj->vertexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)vertices, sizeof(vertices));
  obj->normals = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)normals, sizeof(normals));
  obj->colors = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)colors, sizeof(colors));

  return obj;
}

//
//     B
//   D A E F
//     C
CPrimitive3D* initCPrimitive3DAsCube(CPrimitive3D* obj) {
  initCPrimitive3D(obj);
  CMatrixVertexType vVerticesSet[] = {
    // A 0-3
   -0.5, 0.5, 0.5,    1.0, 1.0, 1.0, 1.0,  0.0, 0.0, 1.0,
   -0.5, -0.5, 0.5,   1.0, 1.0, 1.0, 1.0,  0.0, 0.0, 1.0,
   0.5, -0.5, 0.5,    1.0, 1.0, 1.0, 1.0,  0.0, 0.0, 1.0,
   0.5, 0.5, 0.5,     1.0, 1.0, 1.0, 1.0,  0.0, 0.0, 1.0,
   // F 4-7
   -0.5, 0.5, -0.5,    1.0, 1.0, 1.0, 1.0,  0.0, 0.0, -1.0,
   -0.5, -0.5, -0.5,   1.0, 1.0, 1.0, 1.0,  0.0, 0.0, -1.0,
   0.5, -0.5, -0.5,    1.0, 1.0, 1.0, 1.0,  0.0, 0.0, -1.0,
   0.5, 0.5, -0.5,     1.0, 1.0, 1.0, 1.0,  0.0, 0.0, -1.0,
   // D 8-11
   -0.5, 0.5, 0.5,    1.0, 1.0, 1.0, 1.0,   -1.0, 0.0, 0.0,
   -0.5, -0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   -1.0, 0.0, 0.0,
   -0.5, 0.5, -0.5,    1.0, 1.0, 1.0, 1.0,  -1.0, 0.0, 0.0,
   -0.5, -0.5, -0.5,   1.0, 1.0, 1.0, 1.0,  -1.0, 0.0, 0.0,
   // E 12-15
   0.5, -0.5, 0.5,    1.0, 1.0, 1.0, 1.0,   1.0, 0.0, 0.0,
   0.5, 0.5, 0.5,     1.0, 1.0, 1.0, 1.0,   1.0, 0.0, 0.0,
   0.5, -0.5, -0.5,    1.0, 1.0, 1.0, 1.0,  1.0, 0.0, 0.0,
   0.5, 0.5, -0.5,     1.0, 1.0, 1.0, 1.0,  1.0, 0.0, 0.0,
   // B 16-19
   -0.5, 0.5, 0.5,    1.0, 1.0, 1.0, 1.0,   0.9, 1.0, 0.0,
   0.5, 0.5, 0.5,     1.0, 1.0, 1.0, 1.0,   0.0, 1.0, 0.0,
   -0.5, 0.5, -0.5,    1.0, 1.0, 1.0, 1.0,  0.0, 1.0, 0.0,
   0.5, 0.5, -0.5,     1.0, 1.0, 1.0, 1.0,  0.0, 1.0, 0.0,
   // C 20-23
   -0.5, -0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, -1.0, 0.0,
   0.5, -0.5, 0.5,    1.0, 1.0, 1.0, 1.0,   0.0, -1.0, 0.0,
   -0.5, -0.5, -0.5,   1.0, 1.0, 1.0, 1.0,  0.0, -1.0, 0.0,
   0.5, -0.5, -0.5,    1.0, 1.0, 1.0, 1.0,  0.0, -1.0, 0.0,
  };

  CMatrixVertexType vertices[] = {
    // A 0-3
   -0.5, 0.5, 0.5, -0.5, -0.5, 0.5,  0.5, -0.5, 0.5,  0.5, 0.5, 0.5,
   // F 4-7
   -0.5, 0.5, -0.5, -0.5, -0.5, -0.5,0.5, -0.5, -0.5,0.5, 0.5, -0.5,
   // D 8-11
   -0.5, 0.5, 0.5, -0.5, -0.5, 0.5,-0.5, 0.5, -0.5, -0.5, -0.5, -0.5,
   // E 12-15
   0.5, -0.5, 0.5, 0.5, 0.5, 0.5,0.5, -0.5, -0.5,0.5, 0.5, -0.5,
   // B 16-19
   -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5,
   // C 20-23
   -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, -0.5, -0.5,  0.5, -0.5, -0.5
  };

  CMatrixVertexType normals[] = {
    // A 0-3
   0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
   // F 4-7
    0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0,
   // D 8-11
    -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
   // E 12-15
     1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
   // B 16-19
    0.9, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
   // C 20-23
   0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0,
  };

  CMatrixVertexType colors[] = {
    // A 0-3
   1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
   // F 4-7
   1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
   // D 8-11
   1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
   // E 12-15
   1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
   // B 16-19
   1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
   // C 20-23
   1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0
  };

  CMatrixIndexType indexes[] = {
    0, 1, 2, 0, 2, 3, // A1 A2
    7, 6, 5, 7, 5, 4, // F1 F2
    8, 11, 9, 8, 10, 11,  // D1 D2
    15, 13, 12, 14, 15, 12,  // E1 E2
    16, 17, 18, 18, 17, 19,  // E1 E2
    22, 21, 20, 23, 21, 22,
  };
  obj->vertexSet = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)vVerticesSet, sizeof(vVerticesSet));
  obj->indexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)indexes, sizeof(indexes));
  obj->vertexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)vertices, sizeof(vertices));
  obj->normals = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)normals, sizeof(normals));
  obj->colors = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)colors, sizeof(colors));
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
    return obj->vertexSet->length/sizeof(CMatrixVertexType);
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
    return obj->indexes->length/sizeof(CMatrixIndexType);
  }
}
