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
#define CMIXER_CMUSIC_NAME "cmu"
typedef struct {
  CObject parent;
  Mix_Music *music;
} CMixer;

typedef struct {
  CObject parent;
  int channelId;
  Mix_Chunk *value;
} CMixerChunk;

typedef struct {
  CObject parent;
  Mix_Music *value;
} CMixerMusic;


CMixer* getCMixer();

CMixerChunk* newCMixerChunk(CMemory* mem);
CMixerChunk* initCMixerChunk(CMixerChunk* obj, int channelId, Mix_Chunk* value);

CMixerMusic* newCMixerMusic(CMemory* mem);
CMixerMusic* initCMixerMusic(CMixerMusic* obj, Mix_Music* value);

CMixerChunk* cmixer_createChunk(CMixer* obj, char* path);
CMixerChunk* cmixer_playChunk(CMixer* obj, int channelId, CMixerChunk*, int loop);
CMixerChunk* cmixer_pauseChunk(CMixer* obj, CMixerChunk*);
CMixerChunk* cmixer_resumeChunk(CMixer* obj, CMixerChunk*);
CMixerChunk* cmixer_haltChunk(CMixer* obj, CMixerChunk*);
CMixerChunk* cmixer_setChunkVolume(CMixer* obj, CMixerChunk*, int volume);

CMixerMusic* cmixer_createMusic(CMixer* obj, char* path);
CMixerMusic* cmixer_playMusic(CMixer* obj, CMixerMusic*, int loop);
CMixerMusic* cmixer_pauseMusic(CMixer* obj, CMixerMusic*);
CMixerMusic* cmixer_resumeMusic(CMixer* obj, CMixerMusic*);
CMixerMusic* cmixer_haltMusic(CMixer* obj, CMixerMusic*);
CMixerMusic* cmixer_setMusicVolume(CMixer* obj, CMixerMusic*, int volume);
#endif
