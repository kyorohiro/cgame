#ifndef _H_CIMAGE
#define _H_CIMAGE

#include <SDL_image.h>

#include "core/cobject.h"

#define CIMAGE_MGR_NAME "cig"
#define CIMAGE_NAME "cim"
#define CIMAGE_COLOR_FROMAT_RGBA 9
#define CIMAGE_COLOR_FROMAT_BGRA 13
#define CIMAGE_COLOR_FROMAT_RGB 1
#define CIMAGE_COLOR_FROMAT_BGR 5
#define CIMAGE_COLOR_FROMAT_NONE 0

typedef struct {
  CObject parent;
  SDL_Surface* value;
} CImage;

typedef struct {
  CObject parent;
} CImageMgr;

CImageMgr* getCImageMgr();
CImage* cimageMgr_createImage(CImageMgr* obj, char* path);
CImage* initCImageFromSDLSurface(CImage* obj, SDL_Surface* value);
CImage* newCImage(CMemory* mem);
CImage* initCImage(CImage* obj, char* path);
CImage* initEmptyRPGACImage(CImage* obj, int w, int h);
CImage* createEmptyRPGACImage(int w, int h);

void cimage_update(CImage *srcs, int sx, int sy, int sw, int sh,
                    CImage *dst, int dx, int dy, int dw, int dh);
int cimage_getWidth(CImage* obj);
int cimage_getHeight(CImage* obj);
void* cimage_getPixels(CImage* obj);
int cimage_getColorFormat(CImage* obj);
int cimage_getColorFormatGL(CImage* obj, int def);
#endif
