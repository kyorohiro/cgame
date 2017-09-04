#include "cobject3d.h"
#include "cprimitive3d.h"
#include <stdio.h>


CPrimitive3D* initCPrimitive3DAsTriangle(CPrimitive3D* obj) {
  initCPrimitive3D(obj);
  CMatrixVertexType vertices[] = {
    0.0f, 0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
  };
  CMatrixVertexType normals[] = {
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0
  };
  CMatrixVertexType colors[] = {
     1.0, 1.0, 1.0, 1.0,
     1.0, 1.0, 1.0, 1.0,
     1.0, 1.0, 1.0, 1.0
  };
  CMatrixIndexType indexes[] = {
    0, 1, 2
  };
  obj->indexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)indexes, sizeof(indexes));
  obj->vertexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)vertices, sizeof(vertices));
  obj->normals = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)normals, sizeof(normals));
  obj->colors = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)colors, sizeof(colors));

  return obj;
}
