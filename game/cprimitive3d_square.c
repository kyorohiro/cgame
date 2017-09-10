#include "cobject3d.h"
#include "cprimitive3d.h"
#include <stdio.h>

//
//     B
//   D A E F
//     C
CPrimitive3D* initCPrimitive3DAsSquare(CPrimitive3D* obj) {
  initCPrimitive3D(obj);
  CMatrixVertexType vertices[] = {
   -0.5, 0.5, 0.5, -0.5, -0.5, 0.5,  0.5, -0.5, 0.5,  0.5, 0.5, 0.5, // A 0-3
  };

  CMatrixVertexType normals[] = {
   0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, // A 0-3
  };

  CMatrixVertexType colors[] = {
   1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, // A 0-3
  };

  CMatrixIndexType indexes[] = {
    0, 1, 2, 0, 2, 3, // A1 A2
  };

  CMatrixVertexType texCoords[] = {
   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, // A 0-3
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
