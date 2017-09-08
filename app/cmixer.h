#ifndef _H_CMIXER
#define _H_CMIXER

#ifdef PLATFORM_EMCC
#include <emscripten.h>
#ifdef USE_SDL_2
#include <SDL/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif
#else
#include <SDL_mixer.h>
#endif

#include "core/cobject.h"

#define CMIXER_CHANNEL_NAME "cmc"

typedef struct {
  CObject parent;
  Mix_Music *music;
} CMixer;

CMixer* newCMixer(CMemory* mem);
CMixer* initCMixer(CMixer* obj);

#endif
