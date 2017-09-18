#ifndef _H_SPRITE2D_
#define _H_SPRITE2D_

#include "matrix/cmatrix.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "app/cdynaTexAtlas.h"
#define CSPRITE2D_NAME "spr"

//
//
typedef struct {
  CPrimitive3D parent;
  //
  // cache
  CMatrixVertexType x;
  CMatrixVertexType y;
  CMatrixVertexType z;
  CMatrixVertexType rx;
  CMatrixVertexType ry;
  CMatrixVertexType rz;

  //
  //
  CMatrixVertexType texX;
  CMatrixVertexType texY;
  CMatrixVertexType texZ;
  CMatrixVertexType texRx;
  CMatrixVertexType texRy;
  CMatrixVertexType texRz;

  //
  //
  CMatrixVertexType texBlockX;
  CMatrixVertexType texBlockY;
  CMatrixVertexType texBlockW;
  CMatrixVertexType texBlockH;
  CMatrixVertexType imageW;
  CMatrixVertexType imageH;
} CSprite2D;

CSprite2D* newCSprite2D(CMemory* mem);
CSprite2D* initCSprite2D(CSprite2D*, int width, int height);
CSprite2D* createCSprite2D(int width, int height);

//
// matrix
CSprite2D* csprite2d_setXYZ(CSprite2D*, CMatrixVertexType x, CMatrixVertexType y, CMatrixVertexType z);
CSprite2D* csprite2d_setRXYZ(CSprite2D*, CMatrixVertexType rx, CMatrixVertexType ry, CMatrixVertexType rz);
CSprite2D* csprite2d_update(CSprite2D*);

//
CSprite2D* csprite2d_setImage(CSprite2D*, CImage* img, CDynaBlockSpace* block);
//

CSprite2D* csprite2d_setTexXYZ(CSprite2D*, CMatrixVertexType x, CMatrixVertexType y, CMatrixVertexType z);
CSprite2D* csprite2d_setTexRXYZ(CSprite2D*, CMatrixVertexType rx, CMatrixVertexType ry, CMatrixVertexType rz);
#endif
