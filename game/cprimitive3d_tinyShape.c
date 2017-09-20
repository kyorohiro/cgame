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

      texCoords[i*2+0] = (src[i*2+0]-left) / (right-left);
      texCoords[i*2+1] = (-1.0*src[i*2+1]-bottom) / (top-bottom);

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

CPrimitive3D* cprimitive3d_setTexCoordAsTinyShapeFromBlock(CPrimitive3D* obj, int _x, int _y, int _w, int _h, int _imgW, int _imgH) {
  return cprimitive3d_setTexCoordAsTinyShapeFromBlockWithTrans(obj, NULL, _x, _y, _w, _h, _imgW, _imgH);
}

CPrimitive3D* cprimitive3d_setTexCoordAsTinyShapeFromBlockWithTrans(CPrimitive3D* obj, CMatrix4* _trans, int _x, int _y, int _w, int _h, int _imgW, int _imgH){
  CVMFloat x = (CVMFloat)_x;
  CVMFloat y = (CVMFloat)_y;
  CVMFloat w = (CVMFloat)_w;
  CVMFloat h = (CVMFloat)_h;
  CVMFloat imgW = (CVMFloat)_imgW;
  CVMFloat imgH = (CVMFloat)_imgH;

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

  CVector4Raw tmp;

  for(int i=0;i<vertexNum;i++) {
    texCoords[i*2+0] = (vertexes[i*3+0]-left) / (right-left);
    texCoords[i*2+0] = texCoords[i*2+0]*(w/imgW) + x/imgW;

    texCoords[i*2+1] = (-1*vertexes[i*3+1]-bottom) / (top-bottom);
    texCoords[i*2+1] = texCoords[i*2+1]*(h/imgH) + y/imgH;
    if(_trans != NULL) {
      tmp[0] = texCoords[i*2+0];
      tmp[1] = texCoords[i*2+1];
      tmp[2] = 1.0;
      tmp[3] = 1.0;
      cmatrix4raw_mulVector4Raw(_trans->value, tmp, tmp);
      texCoords[i*2+0] = tmp[0];
      texCoords[i*2+1] = tmp[1];
    }
  }
  return obj;
}
