#include "cobject3d.h"
#include "cprimitive3d.h"
#include <stdio.h>

//
// tex
// (0.0 0.0) - (1.0 0.0)
//     texture
// (0.0 1.0) - (1.1 1.1)
//
// primitbve
//  4 - 1
//  3 - 2
//
CPrimitive3D* initCPrimitive3DAsSquare(CPrimitive3D* obj) {
  initCPrimitive3D(obj);
  CMatrixVertexType vertices[] = {
   0.5, 0.5, 0.0,  0.5, -0.5, 0.0,  -0.5, -0.5, 0.0,  -0.5, 0.5, 0.0, // A 0-3
  };

  CMatrixVertexType normals[] = {
   0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, // A 0-3
  };

  CMatrixVertexType colors[] = {
   1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, // A 0-3
  };

  CMatrixIndexType indexes[] = {
    0, 3, 1, 2, 1, 3, // A1 A2
  };

  CMatrixVertexType texCoords[] = {
   1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, // A 0-3
  };
  obj->indexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)indexes, sizeof(indexes));
  obj->vertexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)vertices, sizeof(vertices));
  obj->normals = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)normals, sizeof(normals));
  obj->colors = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)colors, sizeof(colors));
  obj->texCoords = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)texCoords, sizeof(texCoords));

  return obj;
}

CPrimitive3D* cprimitive3d_setTexCoordAsSquare(CPrimitive3D* obj, CMatrixVertexType x0, CMatrixVertexType y0, CMatrixVertexType x1, CMatrixVertexType y1, CMatrixVertexType x2, CMatrixVertexType y2, CMatrixVertexType x3, CMatrixVertexType y3) {
  CBytes* texCoords = obj->texCoords;
  CMatrixVertexType* v = (CMatrixVertexType*)texCoords->value;
  v[0] = x0;
  v[1] = y0;
  v[2] = x1;
  v[3] = y1;
  v[4] = x2;
  v[5] = y2;
  v[6] = x3;
  v[7] = y3;
  return obj;
}

//
// tex
// (0.0 0.0) - (1.0 0.0)
//     texture
// (0.0 1.0) - (1.1 1.1)
//
// primitbve
//  4 - 1
//  3 - 2
//
CPrimitive3D* cprimitive3d_setTexCoordAsSquareFromBlock(CPrimitive3D* obj, int x, int y, int w, int h, int imgW, int imgH) {
  double _x = 1.0*x/imgW;
  double _y = 1.0*y/imgH;
  double _w = 1.0*w/imgW;
  double _h = 1.0*h/imgH;
  CMatrixVertexType* v = (CMatrixVertexType*)obj->texCoords->value;
  v[0] = _x+_w; //1.0
  v[1] = _y;    //0.0
  v[2] = _x+_w; //1.0;
  v[3] = _y+_h; //1.0;
  v[4] = _x;    //0.0;
  v[5] = _y+_h; //1.0;
  v[6] = _x;    //0.0;
  v[7] = _y;    //0.0;
  return obj;
}
