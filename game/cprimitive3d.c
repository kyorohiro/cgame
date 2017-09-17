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
  if(objTmp->normals != NULL) {
    releaseCObject((CObject*)objTmp->normals);
  }

  freeCObject3D(obj);
}

CPrimitive3D* newCPrimitive3D(CMemory* mem) {
  CPrimitive3D * ret = cmemory_calloc(mem, 1, sizeof(CPrimitive3D));
  ret->parent.parent.cmemory = mem;
  ret->parent.parent.funcFree = freeCPrimitive3D;
  return ret;
}

CPrimitive3D* initCPrimitive3D(CPrimitive3D* obj) {
  initCObject3D((CObject3D*)obj);
  obj->parent.type = CObject3DTypePrimitive;
  return obj;
}

CPrimitive3D* createCPrimitive3DAsCube() {
  return initCPrimitive3DAsCube(newCPrimitive3D(getCMemory()));
}

CPrimitive3D* createCPrimitive3DAsTriangle() {
  return initCPrimitive3DAsTriangle(newCPrimitive3D(getCMemory()));
}

CPrimitive3D* createPrimitive3DAsSquare() {
  return initCPrimitive3DAsSquare(newCPrimitive3D(getCMemory()));
}

CPrimitive3D* createCPrimitive3DAsTinyShape(CMatrixVertexType* src, int length) {
  return initCPrimitive3DAsTinyShape(newCPrimitive3D(getCMemory()), src, length);
}

CPrimitive3D* cprimitive3d_setColor(CPrimitive3D* obj, double r, double g, double b, double a) {
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

void cprimitive3d_show(CPrimitive3D* shapeP) {
  CMatrixVertexType* vertexes  = (CMatrixVertexType*)shapeP->vertexes->value;
  CMatrixVertexType* normals   = (CMatrixVertexType*)shapeP->normals->value;
  CMatrixVertexType* colors    = (CMatrixVertexType*)shapeP->colors->value;
  CMatrixIndexType* indexes    = (CMatrixIndexType*)shapeP->indexes->value;

  printf("[vertex]\r\n");
  for(int i=0;i<shapeP->vertexes->length/3/sizeof(CMatrixVertexType);i++) {
    printf("(%f %f %f)", vertexes[i*3+0], vertexes[i*3+1], vertexes[i*3+2]);
  }
  printf("\r\n");
  printf("\r\n");
  printf("[normals]\r\n");
  for(int i=0;i<shapeP->normals->length/3/sizeof(CMatrixVertexType);i++) {
    printf("(%f %f %f)", normals[i*3+0], normals[i*3+1], normals[i*3+2]);
  }
  printf("\r\n");
  printf("\r\n");
  printf("[colors]\r\n");
  for(int i=0;i<shapeP->colors->length/4/sizeof(CMatrixVertexType);i++) {
    printf("(%f %f %f %f)", colors[i*4+0], colors[i*4+1], colors[i*4+2], colors[i*4+3]);
  }
  printf("\r\n");
  printf("\r\n");
  printf("[tex]\r\n");
  if(shapeP->texCoords != NULL) {
    CMatrixVertexType* texCoords = (CMatrixVertexType*)shapeP->texCoords->value;

    for(int i=0;i<shapeP->texCoords->length/2/sizeof(CMatrixVertexType);i++) {
      printf("(%f %f)", texCoords[i*2+0], texCoords[i*2+1]);
    }
    printf("\r\n");
  }
  printf("\r\n");
  printf("[indexes] %d\r\n", shapeP->indexes->length);
  for(int i=0;i<shapeP->indexes->length/sizeof(CMatrixIndexType);i++) {
    printf("%d ,", (int)indexes[i]);
  }
  printf("\r\n");
}
