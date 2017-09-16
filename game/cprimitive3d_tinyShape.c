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
  obj->indexes   = initCBytes(newCBytes(obj->parent.parent.cmemory), NULL, sizeof(CMatrixIndexType) * (vertexNum-2)*3);

  CMatrixVertexType* vertexes  = (CMatrixVertexType*)obj->vertexes->value;
  CMatrixVertexType* texCoords = (CMatrixVertexType*)obj->texCoords->value;
  CMatrixVertexType* normals   = (CMatrixVertexType*)obj->normals->value;
  CMatrixVertexType* colors    = (CMatrixVertexType*)obj->colors->value;
  CMatrixIndexType* indexes    = (CMatrixIndexType*)obj->indexes->value;

  CMatrixVertexType right = src[0];
  CMatrixVertexType left = src[0];
  CMatrixVertexType top  = src[1];
  CMatrixVertexType bottom = src[1];
  for(int i=0;i<vertexNum;i++) {
    if(left > src[i*2+0]) {
      left = src[i*2+0];
    }
    if(right < src[i*2+0]) {
      right = src[i*2+0];
    }
    if(bottom > src[i*2+1]) {
      bottom = src[i*2+1];
    }
    if(top < src[i*2+1]) {
      top = src[i*2+1];
    }
  }
  //printf(">> %f %f %f %f\r\n", left, right, top, bottom);
  //
  //
  for(int i=0;i<vertexNum;i++) {
      vertexes[i*3+0] = src[i*2+0];
      vertexes[i*3+1] = src[i*2+1];
      vertexes[i*3+2] = 0.0;

      texCoords[i*2+0] = (1.0*(src[i*2+0]-left))/(1.0*(right-left));
      texCoords[i*2+1] = (1.0*(-1*src[i*2+1]-bottom))/(1.0*(top-bottom));

      normals[i*3+0] = 0.0;
      normals[i*3+1] = 0.0;
      normals[i*3+2] = 1.0;

      colors[i*4+0] = 1.0;
      colors[i*4+1] = 1.0;
      colors[i*4+2] = 1.0;
      colors[i*4+3] = 1.0;
  }

  for(int i=0;(i+2)<vertexNum;i+=1) {
    printf("xx\r\n");
    indexes[3*i+0] = 0;
    indexes[3*i+1] = i+1;
    indexes[3*i+2] = i+2;
  }


  return obj;
}

CPrimitive3D* cprimitive3d_setTexCoordAsTinyShapeFromBlock(CPrimitive3D* obj, int x, int y, int w, int h, int imgW, int imgH) {
  int vertexNum = obj->vertexes->length/sizeof(CMatrixVertexType)/3;
  CMatrixVertexType* vertexes  = (CMatrixVertexType*)obj->vertexes->value;
  CMatrixVertexType* texCoords = (CMatrixVertexType*)obj->texCoords->value;
  CMatrixVertexType right = vertexes[0];
  CMatrixVertexType left = vertexes[0];
  CMatrixVertexType top  = vertexes[1];
  CMatrixVertexType bottom = vertexes[1];
  for(int i=0;i<vertexNum;i++) {
    if(left > vertexes[i*3+0]) {
      left = vertexes[i*3+0];
    }
    if(right < vertexes[i*3+0]) {
      right = vertexes[i*3+0];
    }
    if(bottom > vertexes[i*3+1]) {
      bottom = vertexes[i*3+1];
    }
    if(top < vertexes[i*3+1]) {
      top = vertexes[i*3+1];
    }
  }
  // for(int i=0;i<vertexNum;i++) {
  //      texCoords[i*2+0] = (src[i*2+0]-left)/((right-left));
  //      texCoords[i*2+1] = (-1*src[i*2+1]-bottom)/((top-bottom));
  // }

  //left = left+x/imgW;
  //printf("?? %d %d\r\n",h,imgH);
  for(int i=0;i<vertexNum;i++) {
    texCoords[i*2+0] = (1.0*(vertexes[i*3+0]-left))/(1.0*(right-left));
    texCoords[i*2+0] = 1.0*texCoords[i*2+0]*(1.0*w/1.0*imgW) +1.0*x/1.0*imgW;
//    texCoords[i*2+0] *=0.8;

    texCoords[i*2+1] = (1.0*(-1*vertexes[i*3+1]-bottom))/(1.0*(top-bottom));
    texCoords[i*2+1] = 1.0*texCoords[i*2+1]*(1.0*h/1.0*imgH) +1.0*y/1.0*imgH;
//    texCoords[i*2+1] *=0.8;

  }
  return obj;
}
