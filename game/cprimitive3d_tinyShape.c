#include "cobject3d.h"
#include "cprimitive3d.h"
#include <stdio.h>
#include <string.h>

CPrimitive3D* initCPrimitive3DAsTinyShape(CPrimitive3D* obj, CMatrixVertexType* src, int length) {
  initCPrimitive3D(obj);
  int vertexNum = length/2;
  obj->vertexes  = initCBytes(newCBytes(obj->parent.parent.cmemory), NULL, sizeof(CMatrixVertexType) * vertexNum * 3);
  obj->normals   = initCBytes(newCBytes(obj->parent.parent.cmemory), NULL, sizeof(CMatrixVertexType) * vertexNum * 3);
  obj->colors    = initCBytes(newCBytes(obj->parent.parent.cmemory), NULL, sizeof(CMatrixVertexType) * vertexNum * 4);
  obj->texCoords = initCBytes(newCBytes(obj->parent.parent.cmemory), NULL, sizeof(CMatrixVertexType) * vertexNum * 2);
  obj->indexes   = initCBytes(newCBytes(obj->parent.parent.cmemory), NULL, sizeof(CMatrixVertexType) * vertexNum * (vertexNum-2)*3);

  CMatrixVertexType* vertexes  = (CMatrixVertexType*)obj->vertexes->value;
  CMatrixVertexType* texCoords = (CMatrixVertexType*)obj->texCoords->value;
  CMatrixVertexType* normals   = (CMatrixVertexType*)obj->normals->value;
  CMatrixVertexType* colors    = (CMatrixVertexType*)obj->colors->value;
  CMatrixIndexType* indexes    = (CMatrixIndexType*)obj->indexes;

  for(int i=0;i<vertexNum;i++) {
      vertexes[i*3+0] = src[i*2+0];
      vertexes[i*3+1] = src[i*2+1];
      vertexes[i*3+2] = 0.0;

      texCoords[i*2+0] = src[i*2+0];
      texCoords[i*2+1] = src[i*2+1];

      normals[i*3+0] = 0.0;
      normals[i*3+1] = 0.0;
      normals[i*3+2] = 1.0;

      colors[i*3+0] = 1.0;
      colors[i*3+1] = 1.0;
      colors[i*3+2] = 1.0;
      colors[i*3+3] = 1.0;
  }

  for(int i=0;(i+2)<vertexNum;i++) {
    indexes[i*3+0] = 0;
    indexes[i*3+1] = i+1;
    indexes[i*3+1] = i+2;
  }


  return obj;
}
