#ifndef _H_3DLIGHT
#define _H_3DLIGHT


#include "core/cobject.h"
#include "core/cmemory.h"
#include "vectorMath/cmatrix4.h"
#include "core/cbytes.h"
#include "core/clinkedList.h"
#include "vectorMath/cmatrix4.h"
#include "cobject3d.h"
#define LIGHT3D_NAME "li3"

//
//
typedef struct {
  CObject3D parent;
} CLight3D;

CLight3D* newCLight3D(CMemory* mem);
CLight3D* initCLight3D(CLight3D*);
#endif
