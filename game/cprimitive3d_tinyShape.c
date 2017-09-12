#include "cobject3d.h"
#include "cprimitive3d.h"
#include <stdio.h>

//
//     B
//   D A E F
//     C
CPrimitive3D* initCPrimitive3DAsTinyShape(CPrimitive3D* obj, CMatrixValueType* src){
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
