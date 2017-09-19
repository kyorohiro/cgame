#ifndef _H_CTTF
#define _H_CTTF

#if PLATFORM_EMCC
#ifdef USE_SDL_2
#include <SDL/SDL_ttf.h>
#define SDL2xEMCC_TTF
#else
#include <SDL_ttf.h>
#endif
#else
#include <SDL_ttf.h>
#endif
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
void cttf_sizeText(CTtf*, char *text, int *w, int *h);
#endif
