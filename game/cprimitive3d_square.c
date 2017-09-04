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
    // A 0-3
   -0.5, 0.5, 0.5, -0.5, -0.5, 0.5,  0.5, -0.5, 0.5,  0.5, 0.5, 0.5,
  };

  CMatrixVertexType normals[] = {
    // A 0-3
   0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
  };

  CMatrixVertexType colors[] = {
    // A 0-3
   1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
  };

  CMatrixIndexType indexes[] = {
    0, 1, 2, 0, 2, 3, // A1 A2
  };
  obj->indexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)indexes, sizeof(indexes));
  obj->vertexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)vertices, sizeof(vertices));
  obj->normals = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)normals, sizeof(normals));
  obj->colors = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)colors, sizeof(colors));
  return obj;
}
