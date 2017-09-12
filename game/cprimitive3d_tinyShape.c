#include "cobject3d.h"
#include "cprimitive3d.h"
#include <stdio.h>
#include <string.h>

CPrimitive3D* initCPrimitive3DAsTinyShape(CPrimitive3D* obj, CMatrixVertexType* src, int length) {
  initCPrimitive3D(obj);

  obj->vertexes  = initCBytes(newCBytes(obj->parent.parent.cmemory), NULL, sizeof(CMatrixVertexType) * length / 2 * 3);
  obj->normals   = initCBytes(newCBytes(obj->parent.parent.cmemory), NULL, sizeof(CMatrixVertexType) * length / 2 * 3);
  obj->colors    = initCBytes(newCBytes(obj->parent.parent.cmemory), NULL, sizeof(CMatrixVertexType) * length / 2 * 4);
  obj->texCoords = initCBytes(newCBytes(obj->parent.parent.cmemory), NULL, sizeof(CMatrixVertexType) * length / 2 * 2);

  for(int i=0;i<length/2;i++) {
      obj->vertexes->value[i*3+0] = src[i*2+0];
      obj->vertexes->value[i*3+1] = src[i*2+1];
      obj->vertexes->value[i*3+2] = 0.0;

      obj->texCoords->value[i*2+0] = src[i*2+0];
      obj->texCoords->value[i*2+1] = src[i*2+1];

      obj->normals->value[i*3+0] = 0.0;
      obj->normals->value[i*3+1] = 0.0;
      obj->normals->value[i*3+2] = 1.0;

      obj->colors->value[i*3+0] = 1.0;
      obj->colors->value[i*3+1] = 1.0;
      obj->colors->value[i*3+2] = 1.0;
      obj->colors->value[i*3+3] = 1.0;
  }


  CMatrixIndexType indexes[] = {
    0, 3, 1, 2, 1, 3, // A1 A2
  };

  obj->indexes = initCBytes(newCBytes(obj->parent.parent.cmemory), (char*)indexes, sizeof(indexes));



  return obj;
}
