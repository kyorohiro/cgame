#ifndef _H_CIMAGE
#define _H_CIMAGE

#include <SDL_image.h>

#include "core/cobject.h"

#ifdef USE_SDL_1
#ifdef PLATFORM_EMCC
#define CIMAGE_UNUSE_SCREEN_LOCK
#define CIMAGE_USE_MANUALL_COPY
#else
#define CIMAGE_USE_DISPLAY_FORMAT
#endif
#endif


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

CImage* newCImage(CMemory* mem);
CImage* initCImageFromSDLSurface(CImage* obj, SDL_Surface* value);
CImage* initCImage(CImage* obj, char* path);
CImage* initEmptyRPGACImage(CImage* obj, int w, int h);
CImage* createEmptyRPGACImage(int w, int h);

void cimage_update(CImage *dst, int dx, int dy, int dw, int dh,
                    CImage *src, int sx, int sy, int sw, int sh);
void cimage_updateFromSDLSurface(CImage *dst, int dx, int dy, int dw, int dh,
                    SDL_Surface*, int sx, int sy, int sw, int sh);
void cimage_updateFromSDLSurface2(CImage *dst, int dx, int dy, int dw, int dh,
                    SDL_Surface*, int sx, int sy, int sw, int sh);
int cimage_getWidth(CImage* obj);
int cimage_getHeight(CImage* obj);
void* cimage_getPixels(CImage* obj);
int cimage_getColorFormat(CImage* obj);
int cimage_getColorFormatGL(CImage* obj, int def);
int cimage_getColorFormatFromSDLSurface(SDL_Surface* value);
int cimage_getBytesPerPixel(SDL_Surface* value);
void cimage_clear(CImage* obj);
SDL_Surface* cimageUtil_loadFromPath(char *path);
#endif
