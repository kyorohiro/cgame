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

void _freeCMixerMusic(void* obj) {
  CObject *objObj = (CObject*)obj;
  CMixerMusic *mixObj = (CMixerMusic*)obj;
  if(mixObj->value != NULL) {
    Mix_FreeMusic(mixObj->value);
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

CMixerChunk* initCMixerChunk(CMixerChunk* obj, int channelId, Mix_Chunk* value) {
  initCObject((CObject*)obj, CMIXER_CHANNEL_NAME);
  obj->value = value;
  obj->channelId = channelId;
  return obj;
}

CMixerMusic* newCMixerMusic(CMemory* cmemory) {
  CMixerMusic* ret = (CMixerMusic*)cmemory_calloc(cmemory, 1, sizeof(CMixerMusic));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCMixerMusic;
  return ret;
}

CMixerMusic* initCMixerMusic(CMixerMusic* obj, Mix_Music* value) {
  initCObject((CObject*)obj, CMIXER_CMUSIC_NAME);
  obj->value = value;
  return obj;
}


CMixerChunk* cmixer_createChunk(CMixer* obj, char* path) {
  CMemory* mem = cobject_getCMemory((CObject*)obj);
  Mix_Chunk* chunk = Mix_LoadWAV(path);
  if( chunk == NULL) {
    printf("Failed at Mix_LoadWAV\r\n");
    return NULL;
  }
  CMixerChunk* ret = initCMixerChunk(newCMixerChunk(mem), 0, chunk);
  return ret;
}


CMixerChunk* cmixer_playChunk(CMixer* obj, int channelId, CMixerChunk* objCh, int loop) {
  if( Mix_PlayChannel( channelId, objCh->value, loop ) == -1 ) {
    printf("Failed at Mix_PlayChannel\r\n");
    return objCh;
  }
  objCh->channelId = channelId;
  return objCh;
}

CMixerChunk* cmixer_setChunkVolume(CMixer* obj, CMixerChunk* objCh, int volume) {
  Mix_VolumeChunk(objCh->value, volume);
  return objCh;
}

CMixerChunk* cmixer_pauseChunk(CMixer* obj, CMixerChunk* objCh) {
  Mix_Pause(objCh->channelId);
  return objCh;
}

CMixerChunk* cmixer_resumeChunk(CMixer* obj, CMixerChunk* objCh) {
  Mix_Resume(objCh->channelId);
  return objCh;
}

CMixerChunk* cmixer_haltChunk(CMixer* obj, CMixerChunk* objCh) {
  Mix_HaltChannel(objCh->channelId);
  return objCh;
}
