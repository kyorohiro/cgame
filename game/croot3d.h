#ifndef _H_3DROOT
#define _H_3DROOT


#include "core/cobject.h"
#include "core/cmemory.h"
#include "matrix/cmatrix4.h"
#include "core/cbytes.h"
#include "core/carrayList.h"
#include "matrix/cmatrix4.h"

#define ROOT3D_NAME "ro3"
//
//
typedef struct {
  CObject3D parent;
  int index;
  CArrayList *matrixList;
} CRoot3D;

CRoot3D* newCRoot3D(CMemory* mem);
CRoot3D* initCRoot3D(CRoot3D* obj, int depth);
CRoot3D* croot3d_pushMulMatrix(CRoot3D* obj, CMatrix4 *mat);
CMatrix4* croot3d_popMulMatrix(CRoot3D* obj);
CMatrix4* croot3d_peekMulMatrix(CRoot3D* obj);
#endif
