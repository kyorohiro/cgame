#ifndef _H_CTEX_ATLAS_
#define _H_CTEX_ATLAS_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cimage.h"

typedef struct {
  CObject parent;
  CImage* image;
} CTexAtlas;

typedef struct {
  int x;
  int y;
  int w;
  int h;
} TextAtlasBlockRaw;

#define CTEX_ATLAS_NAME "cta"
CTexAtlas* newCTexAtlas(CMemory*);
CTexAtlas* initCTexAtlas(CTexAtlas*, int w, int h);
CTexAtlas* createCTexAtlas(int w, int h);

#endif
