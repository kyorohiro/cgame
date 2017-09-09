#ifndef _H_CIMAGE
#define _H_CIMAGE

#include <SDL_image.h>

#include "core/cobject.h"

#define CIMAGE_MGR_NAME "cig"
#define CIMAGE_NAME "cim"

typedef struct {
  CObject parent;
  SDL_Surface* value;
} CImage;

typedef struct {
  CObject parent;
} CImageMgr;

CImageMgr* getCImageMgr(CMemory* mem);
CImage* cimageMgr_createImage(CImageMgr* obj, char* path);


#endif
