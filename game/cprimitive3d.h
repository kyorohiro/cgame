#ifndef _H_3DPRIMITIVE
#define _H_3DPRIMITIVE


#include "core/cobject.h"
#include "core/cmemory.h"
#include "matrix/cmatrix4.h"
#include "core/cbytes.h"
#include "core/clinkedList.h"
#include "matrix/cmatrix4.h"

#define PRIMITIVE3D_NAME "pr3"
#define PRIMITIVE3D_BUFFER_SIZE 10
//
//
typedef struct {
  CObject3D parent;
  double x;
  double y;
  double z;
  double rx;
  double ry;
  double rz;
  int status;
  double ca;
  double cr;
  double cg;
  double cb;
  CBytes *vertexSet;
  CBytes *vertexes;
  CBytes *normals;
  CBytes *colors;
  CBytes *indexes;
  int vetexUnitSize;
} CPrimitive3D;

CPrimitive3D* newCPrimitive3D(CMemory* mem);
CPrimitive3D* initCPrimitive3D(CPrimitive3D*);
CPrimitive3D* initCPrimitive3DAsCube(CPrimitive3D*);
CPrimitive3D* initCPrimitive3DAsTriangle(CPrimitive3D* obj);
void freeCPrimitive3D(void* obj);
CPrimitive3D* cprimitive3d_setColor(CPrimitive3D*, double a, double r, double g, double b);

char* cprimitive3d_getVertexBinary(CPrimitive3D*);
int cprimitive3d_getVertexBinaryLength(CPrimitive3D*);
char* cprimitive3d_getIndexBinary(CPrimitive3D*);
int cprimitive3d_getIndexBinaryLength(CPrimitive3D*);
#endif
