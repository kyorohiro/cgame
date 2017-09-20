#ifndef _H_3DPRIMITIVE
#define _H_3DPRIMITIVE


#include "core/cobject.h"
#include "core/cmemory.h"
#include "vectorMath/cmatrix4.h"
#include "core/cbytes.h"
#include "core/clinkedList.h"
#include "vectorMath/cmatrix4.h"
#include "cobject3d.h"
#include "cprimitive3d.h"

#define SPRITE3D_NAME "sp3"

//
//
typedef struct {
  CPrimitive3D parent;
} CSprite;

CSprite* newCSprite(CMemory* mem);
CSprite* initCSpriteFromSingleImage(CSprite*, char* imgPath);

#endif
