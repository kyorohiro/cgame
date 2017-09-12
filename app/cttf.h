#ifndef _H_CTTF
#define _H_CTTF

#include <SDL_ttf.h>

#include "core/cobject.h"
#include "cimage.h"

#define CTTF_MGR_NAME "cttfm"
#define CTTF_NAME "cttf"

typedef struct {
  CObject parent;
} CTtfMgr;

typedef struct {
  CObject parent;
  TTF_Font *value;
} CTtf;

CTtfMgr* getCTtfMgr();
CTtf* cttfMgr_createTtf(CTtfMgr*, char* path, int size);
CImage* cttf_createCImageAtSolid(CTtf*, char *text, double r, double g, double b, double a);
CImage* cttf_createCImageAtShaded(CTtf*, char *text, double r, double g, double b, double a);
CImage* cttf_createCImageAtBlended(CTtf*, char *text, double r, double g, double b, double a);
SDL_Surface* cttf_createSDLSurfaceAtSolid(CTtf*, char *text, double r, double g, double b, double a);
#endif
