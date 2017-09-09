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

CImageMgr* getCImageMgr(CMemory* mem);
CImage* cimageMgr_createImage(CImageMgr* obj, char* path);
CImage* initCImageFromSDLSurface(CImage* obj, SDL_Surface* value);
CImage* newCImage(CMemory* mem);


int cimage_getWidth(CImage* obj);
int cimage_getHeight(CImage* obj);
void* cimage_getPixels(CImage* obj);
int cimage_getColorFormat(CImage* obj);
int cimage_getColorFormatGL(CImage* obj, int def);
#endif
