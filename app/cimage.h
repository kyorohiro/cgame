#ifndef _H_CIMAGE
#define _H_CIMAGE

#include <SDL_image.h>

#include "core/cobject.h"

#define CIMAGE_NAME "cim"

typedef struct {
  CObject parent;
  SDL_Surface* value;
} CImage;


CImage* newCImage(CMemory* mem);
CImage* initCImage(CImage* obj, char* path);


#endif
