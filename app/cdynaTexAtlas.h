#ifndef _H_CTEX_ATLAS_
#define _H_CTEX_ATLAS_

#include "core/cobject.h"
#include "core/cmemory.h"

#include "utils/cdynablock.h"
#include "cimage.h"

typedef struct {
  CObject parent;
  CImage* image;
  CDynaBlock* block;
} CDynaTexAtlas;

typedef struct {
  int x;
  int y;
  int w;
  int h;
} TexAtlasBlockRaw;

#define CTEX_ATLAS_NAME "cta"
CDynaTexAtlas* newCDynaTexAtlas(CMemory*);
CDynaTexAtlas* initCDynaTexAtlas(CDynaTexAtlas*, int w, int h);
CDynaTexAtlas* createCDynaTexAtlas(int w, int h);

int ctexAtlas_addImage(CDynaTexAtlas* obj, CImage *src, int sx, int sy, int sw, int sh, CDynaBlockSpace* out);
int ctexAtlas_addImageManually(CDynaTexAtlas* obj, int dx, int dy, int dw, int dh, CImage *src, int sx, int sy, int sw, int sh);

#endif
