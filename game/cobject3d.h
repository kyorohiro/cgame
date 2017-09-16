#ifndef _H_3DOBJECT
#define _H_3DOBJECT
//typedef int (*free)(int n);

#include "core/cobject.h"
#include "core/cmemory.h"
#include "matrix/cmatrix4.h"
#include "core/cbytes.h"
#include "core/clinkedList.h"
#include "matrix/cmatrix4.h"
#include "matrix/cmatrix_proj.h"
#define OBJECT3D_NAME "ob3"

#define CObject3DTypeObject 0
#define CObject3DTypePrimitive 1
#define CObject3DTypeCamera 2
#define CObject3DTypeLight 3
#define CObject3DTypeRoot 4

typedef void (*CObject3DFuncOnEnterFrame)(CObject*  obj, CObject* cgame);
typedef struct {
  CObject parent;
  CMatrix4 *mat;
  CMatrix4 *arg;
  //
  CLinkedList *nodes;
  CObject3DFuncOnEnterFrame onEnterFrameFunc;
  int isLeaf;
  int type;
  //
  //
  // todo
  CMatrixValueType centerX;
  CMatrixValueType centerY;
  CMatrixValueType centerZ;
  CMatrixValueType width; // x
  CMatrixValueType height; // y
  CMatrixValueType length; // z
} CObject3D;


CObject3D* newCObject3D(CMemory* mem);
CObject3D* initCObject3D(CObject3D*);
void freeCObject3D(void* obj);
CObject3D* cobject3d_setOnEnterFrameFunc(CObject3D* obj, CObject3DFuncOnEnterFrame func);


CObject3D* cobject3d_addNode(CObject3D*, CObject3D* node);
CMatrix4* cobject3d_getCMatrix4(CObject3D*);
CLinkedList* cobject3d_getNodes(CObject3D*);
void cobject3d_enterFrame(CObject3D* obj, CObject3D* root, CObject* cgame);


#endif
