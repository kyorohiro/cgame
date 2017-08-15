#ifndef _H_3DROOT
#define _H_3DROOT


#include "core/cobject.h"
#include "core/cmemory.h"
#include "matrix/cmatrix4.h"
#include "core/cbytes.h"
#include "core/clinkedList.h"
#include "matrix/cmatrix4.h"

#define ROOT3D_NAME "ro3"
//
//
typedef struct {
  CObject3D parent;

} CRoot3D;

CRoot3D* newCRoot3D(CMemory* mem);
CRoot3D* initCRoot3D(CRoot3D*);
#endif
