#ifndef _H_TEXT2D_
#define _H_TEXT2D_

#include "csprite2d.h"
#include "matrix/cmatrix.h"
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
CText2D* initCText2D(CText2D*, int width, int height, CDynaTexAtlas* atlas, char *text);
CText2D* createCText2D(int width, int height, CDynaTexAtlas* atlas, char *text);

#endif
