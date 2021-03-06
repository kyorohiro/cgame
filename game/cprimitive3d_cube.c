#include "cobject3d.h"
#include "cprimitive3d.h"
#include <stdio.h>

//
//     B
//   D A E F
//     C
CPrimitive3D* initCPrimitive3DAsCube(CPrimitive3D* obj) {
  initCPrimitive3D(obj);
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
   0.0, 0.0, 1.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,
   // F 4-7
    0.0, 0.0, -1.0,  0.0, 0.0, -1.0,  0.0, 0.0, -1.0,  0.0, 0.0, -1.0,
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
  obj->indexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)indexes, sizeof(indexes));
  obj->vertexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)vertices, sizeof(vertices));
  obj->normals = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)normals, sizeof(normals));
  obj->colors = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)colors, sizeof(colors));
  return obj;
}
