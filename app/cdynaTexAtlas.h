#ifndef _H_CTEX_ATLAS_
#define _H_CTEX_ATLAS_

#include "core/cobject.h"
#include "core/cmemory.h"

#include "cdynablock.h"
#include "cimage.h"
#include "cttf.h"

typedef struct {
  CObject parent;
  CImage* image;
  CDynaBlock* block;
} CDynaTexAtlas;
/*
typedef struct {
  int x;
  int y;
  int w;
  int h;
} STexAtlasBlock;
*/
#define CTEX_ATLAS_NAME "cta"
CDynaTexAtlas* newCDynaTexAtlas(CMemory*);
CDynaTexAtlas* initCDynaTexAtlas(CDynaTexAtlas*, int w, int h);
CDynaTexAtlas* createCDynaTexAtlas(int w, int h);
CDynaTexAtlas* ctexAtlas_clear(CDynaTexAtlas*);

int ctexAtlas_addImage(CDynaTexAtlas* obj, CImage *src, int sx, int sy, int sw, int sh, CDynaBlockSpace* out);
int ctexAtlas_addImageManually(CDynaTexAtlas* obj, int dx, int dy, int dw, int dh, CImage *src, int sx, int sy, int sw, int sh);
CImage* ctexAtlas_getImage(CDynaTexAtlas* obj);
int ctexAtlas_getWidth(CDynaTexAtlas* obj);
int ctexAtlas_getHeight(CDynaTexAtlas* obj);
int ctexAtlas_addImageFromPath(CDynaTexAtlas* obj, char* path, CDynaBlockSpace* out);
int ctexAtlas_addImageFromCTtf(CDynaTexAtlas* obj, CTtf*, char *text, double r, double g, double b, double a, CDynaBlockSpace* out);
int ctexAtlas_addImageFromSDLSurface(CDynaTexAtlas* obj, SDL_Surface* value, CDynaBlockSpace* out);
#endif
