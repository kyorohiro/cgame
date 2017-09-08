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
  int channelId;
  Mix_Chunk *value;
} CMixerChunk;

CMixer* newCMixer(CMemory* mem);
CMixer* initCMixer(CMixer* obj);

CMixerChunk* newCMixerChunk(CMemory* mem);
CMixerChunk* initCMixerChunk(CMixerChunk* obj, int channelId, Mix_Chunk* value);

CMixerChunk* cmixer_createChunk(CMixer* obj, char* path);
CMixerChunk* cmixer_playChunk(CMixer* obj, int channelId, CMixerChunk*, int loop);
CMixerChunk* cmixer_pauseChunk(CMixer* obj, CMixerChunk*);
CMixerChunk* cmixer_resumeChunk(CMixer* obj, CMixerChunk*);
CMixerChunk* cmixer_haltChunk(CMixer* obj, CMixerChunk*);
CMixerChunk* cmixer_setChunkVolume(CMixer* obj, CMixerChunk*, int volume);

#endif
