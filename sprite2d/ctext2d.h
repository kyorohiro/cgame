#ifndef _H_TEXT2D_
#define _H_TEXT2D_

#include "csprite2d.h"
#include "vectorMath/cmatrix.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "app/cdynaTexAtlas.h"
#include "core/cstring.h"

#define CTEXT2D_NAME "spr"

//
//
typedef struct {
  CSprite2D parent;
  //
  CString* text;
  CDynaTexAtlas* atlas;

  int speed;
} CText2D;

CText2D* newCText2D(CMemory* mem);
CText2D* initCText2D(CText2D*, CMatrixVertexType width, CMatrixVertexType height, CDynaTexAtlas* atlas, char *text);
CText2D* createCText2D(CMatrixVertexType width, CMatrixVertexType height, CDynaTexAtlas* atlas, char *text);

#endif
