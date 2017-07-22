#ifndef _H_3DOBJECT
#define _H_3DOBJECT
//typedef int (*free)(int n);

#include "core/object.h"
#include "core/cmemory.h"
#include "glmatrix/glmatrix.h"

#define OBJECT3D_NAME "ob3";

typedef struct {
  CObject parent;
  double x;
  double y;
  double z;
  double rx;
  double ry;
  double rz;
  KMatrix *mat;
} Object3D;

//
// unused CGame is singleton
//
Object3D* newObject3D(CMemory* mem);
//char* title, int width, int height
Object3D* initObject3D(Object3D*);
Object3D* object3d_setRotate(Object3D*, double rx, double ry, double rz);

#endif
