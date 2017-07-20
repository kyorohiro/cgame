#ifndef _H_3DOBJECT
#define _H_3DOBJECT
//typedef int (*free)(int n);

#include "core/object.h"
#include "core/cmemory.h"

#define CGAME_NAME "cga";

typedef struct {
  CObject parent;
} Object3D;

//
// unused CGame is singleton
//
Object3D* new3DObject(CMemory* mem);
//char* title, int width, int height
Object3D* init3DObject(Object3D*, char* name);

#endif
