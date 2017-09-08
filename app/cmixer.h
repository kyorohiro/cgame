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

#define CMIXER_CMIXER_NAME "cmx"
#define CMIXER_CHANNEL_NAME "cmc"
typedef struct {
  CObject parent;
  Mix_Music *music;
} CMixer;

typedef struct {
  CObject parent;
  Mix_Chunk *value;
} CMixerChunk;

CMixer* newCMixer(CMemory* mem);
CMixer* initCMixer(CMixer* obj);
CMixerChunk* cmixer_createChunk(CMixer* obj, char* path);


CMixerChunk* newCMixerChunk(CMemory* mem);
CMixerChunk* initCMixerChunk(CMixerChunk* obj, Mix_Chunk* value);

CMixerChunk* cmixerChunk_play(CMixerChunk* obj, int channelId, int loop);
CMixerChunk* cmixerChunk_setVolume(CMixerChunk* obj, int volume);

#endif
