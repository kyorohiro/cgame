#ifndef _H_3DOBJECT
#define _H_3DOBJECT
//typedef int (*free)(int n);

#include "core/cobject.h"
#include "core/cmemory.h"
#include "glmatrix/glmatrix.h"

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
  KMatrix *mat;
  KMatrix *arg;
} CObject3D;

//
// unused CGame is singleton
//
CObject3D* newCObject3D(CMemory* mem);
//char* title, int width, int height
CObject3D* initCObject3D(CObject3D*);
CObject3D* cobject3d_setRotate(CObject3D*, double rx, double ry, double rz);
CObject3D* cobject3d_setPosition(CObject3D*, double x, double y, double z);
KMatrix* cobject3d_getKMatrix(CObject3D*);

#endif
