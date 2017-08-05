#ifndef _H_3DOBJECT
#define _H_3DOBJECT
//typedef int (*free)(int n);

#include "core/cobject.h"
#include "core/cmemory.h"
#include "matrix/cmatrix4.h"
#include "core/cbytes.h"
#include "core/clinkedList.h"
#include "matrix/cmatrix4.h"
#define OBJECT3D_NAME "ob3"

typedef struct {
  CObject parent;
  double x;
  double y;
  double z;
  double rx;
  double ry;
  double rz;
  int status;
  CMatrix4 *mat;
  CMatrix4 *arg;
  //
  CBytes *vertexs;
  //
  CLinkedList *nodes;
} CObject3D;

CObject3D* newCObject3D(CMemory* mem);
CObject3D* initCObject3D(CObject3D*);
void freeCObject3D(void* obj);
CObject3D* cobject3d_setRotate(CObject3D*, double rx, double ry, double rz);
CObject3D* cobject3d_setPosition(CObject3D*, double x, double y, double z);
CObject3D* cobject3d_addNode(CObject3D*, CObject3D* node);
CMatrix4* cobject3d_getCMatrix4(CObject3D*);
CObject3D* initCObject3DAsCube(CObject3D*);
char* cobject3d_getVertexBinary(CObject3D*);
int cobject3d_getVertexBinaryLength(CObject3D*);
CLinkedList* cobject3d_getNodes(CObject3D*);
#endif
