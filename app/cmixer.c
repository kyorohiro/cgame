#include "cmixer.h"


void _freeCMixer(void* obj) {
  CObject *objObj = (CObject*)obj;
  CMixer *mixObj = (CMixer*)obj;
  // Mix_FreeChunk( scratch );
  Mix_CloseAudio();
  freeCObject(obj);
}

void _freeCMixerChunk(void* obj) {
  CObject *objObj = (CObject*)obj;
  CMixerChunk *mixObj = (CMixerChunk*)obj;
  if(mixObj->value != NULL) {
    Mix_FreeChunk(mixObj->value);
    mixObj = NULL;
  }
  freeCObject(obj);
}

CMixer* newCMixer(CMemory* cmemory) {
  CMixer* ret = (CMixer*)cmemory_calloc(cmemory, 1, sizeof(CMixer));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCMixer;
  return ret;
}

CMixer* initCMixer(CMixer* obj){
  initCObject((CObject*)obj, CMIXER_CMIXER_NAME);
  Mix_Init(MIX_INIT_OGG);
  int result = 0;
  if (MIX_INIT_OGG != (result = Mix_Init(MIX_INIT_OGG))) {
      printf("Mix_Init: %s\n", Mix_GetError());
  }
  if( Mix_OpenAudio( 0, 0,0, 0 ) < 0 ){
    printf("Failed at Mix_OpenAudio\r\n");
  }
  return obj;
}

CMixerChunk* newCMixerChunk(CMemory* cmemory) {
  CMixerChunk* ret = (CMixerChunk*)cmemory_calloc(cmemory, 1, sizeof(CMixerChunk));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCMixerChunk;
  return ret;
}

CMixerChunk* initCMixerChunk(CMixerChunk* obj, Mix_Chunk* value) {
  initCObject((CObject*)obj, CMIXER_CHANNEL_NAME);
  obj->value = value;
  return obj;
}

CMixerChunk* cmixer_createChunk(CMixer* obj, char* path){
  CMemory* mem = cobject_getCMemory((CObject*)obj);
  Mix_Chunk* chunk = Mix_LoadWAV(path);
  if( chunk == NULL) {
    printf("Failed at Mix_LoadWAV\r\n");
    return NULL;
  }
  CMixerChunk* ret = initCMixerChunk(newCMixerChunk(mem),chunk);
  return ret;
}

CMixerChunk* cmixerChunk_play(CMixerChunk* obj, int channelId, int loop) {
  if( Mix_PlayChannel( channelId, obj->value, loop ) == -1 ) {
    printf("Failed at Mix_PlayChannel\r\n");
    return obj;
  }
  return obj;
}

CMixerChunk* cmixerChunk_setVolume(CMixerChunk* obj, int volume) {
  Mix_VolumeChunk(obj->value, volume);
  return obj;
}
