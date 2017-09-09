#ifndef _H_CIMAGE
#define _H_CIMAGE

#include <SDL_ttf.h>

#include "core/cobject.h"

#define CTTF_MGR_NAME "cttfm"
#define CTTF_NAME "cttf"

typedef struct {
  CObject parent;
} CTtfMgr;

typedef struct {
  CObject parent;
} CTtf;

CTtfMgr* getCTtfMgr(CMemory* mem);

#endif
