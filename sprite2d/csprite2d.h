#ifndef _H_SPRITE2D_
#define _H_SPRITE2D_

#include "vectorMath/cvectorMath.h"
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
  CMatrix4* texMat;
  CMatrixVertexType texX; // position
  CMatrixVertexType texY;
  CMatrixVertexType texZ;
  CMatrixVertexType texRx; //roatate
  CMatrixVertexType texRy;
  CMatrixVertexType texRz;

  CMatrixVertexType texCx; //center
  CMatrixVertexType texCy;
  CMatrixVertexType texCz;

  //
  //
  CMatrixVertexType texBlockX;
  CMatrixVertexType texBlockY;
  CMatrixVertexType texBlockW;
  CMatrixVertexType texBlockH;
  CMatrixVertexType imageW;
  CMatrixVertexType imageH;
} CSprite2D;

void freeCSprite2D(void* obj);
CSprite2D* newCSprite2D(CMemory* mem);
CSprite2D* initCSprite2D(CSprite2D*, CMatrixVertexType width, CMatrixVertexType height);
CSprite2D* createCSprite2D(CMatrixVertexType width, CMatrixVertexType height);

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
CSprite2D* csprite2d_updateTex(CSprite2D* obj);
#endif
