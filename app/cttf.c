#include "cttf.h"
#include <stdio.h>
#include <SDL_opengl.h>
#include "cimage.h"

CTtfMgr* newCTtfMgr(CMemory* mem);
CTtfMgr* initCTtfMgr(CTtfMgr* obj);
CTtf* newCTtf(CMemory* mem);
CTtf* initCTtf(CTtf* obj, char* path, int size);

CTtfMgr* defaultCTtfMgr = NULL;
CTtfMgr* getCTtfMgr(CMemory* mem) {
  if(defaultCTtfMgr == NULL) {
    defaultCTtfMgr = initCTtfMgr(newCTtfMgr(getCMemory()));
  }
  return defaultCTtfMgr;
}

void _freeCTtfMgr(void* obj) {
  CObject *objObj = (CObject*)obj;
  CTtfMgr *ttfMgrObj = (CTtfMgr*)obj;
  TTF_Quit();
  freeCObject(obj);
}

CTtfMgr* newCTtfMgr(CMemory* cmemory) {
  CTtfMgr* ret = (CTtfMgr*)cmemory_calloc(cmemory, 1, sizeof(CTtfMgr));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCTtfMgr;
  return ret;
}

CTtfMgr* initCTtfMgr(CTtfMgr* obj) {
  initCObject((CObject*)obj, CTTF_MGR_NAME);
  TTF_Init();
  return obj;
}


void _freeCTtf(void* obj) {
  CObject *objObj = (CObject*)obj;
  CTtf *ttfObj = (CTtf*)obj;
  if(ttfObj->value == NULL) {
    TTF_CloseFont(ttfObj->value);
  }
  freeCObject(obj);
}

CTtf* newCTtf(CMemory* cmemory) {
  CTtf* ret = (CTtf*)cmemory_calloc(cmemory, 1, sizeof(CTtf));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCTtf;
  return ret;
}

CTtf* initCTtf(CTtf* obj, char* path, int size) {
  initCObject((CObject*)obj, CTTF_NAME);
  TTF_Font *font = TTF_OpenFont(path, size);
  obj->value = font;
  return obj;
}


CTtf* cttfMgr_createTtf(CTtfMgr* obj, char* path, int size) {
  CMemory* mem = cobject_getCMemory((CObject*)obj);
  return initCTtf(newCTtf(mem), path, size);
}

CImage* cttf_createCImageAtSolid(CTtf* obj, char *text, double r, double g, double b, double a) {
  SDL_Color fg;fg.r=255*r;fg.g=255*g;fg.b=255*b;fg.a =255*a;
  SDL_Surface* surface = TTF_RenderUTF8_Solid(obj->value, text, fg);
  CMemory* mem = cobject_getCMemory((CObject*)obj);
  return initCImageFromSDLSurface(newCImage(mem), surface);
}

CImage*  cttf_createCImageAtShaded(CTtf* obj, char *text, double r, double g, double b, double a) {
  SDL_Color fg;fg.r=255*r;fg.g=255*g;fg.b=255*b;fg.a =255*a;
  SDL_Color bg = {0xff,0xff,0xff,0xff};
  SDL_Surface* surface = TTF_RenderUTF8_Shaded(obj->value, text, fg, bg);
  CMemory* mem = cobject_getCMemory((CObject*)obj);
  return initCImageFromSDLSurface(newCImage(mem), surface);
}

CImage* cttf_createCImageAtBlended(CTtf* obj, char *text, double r, double g, double b, double a) {
  SDL_Color fg;fg.r=255*r;fg.g=255*g;fg.b=255*b;fg.a =255*a;
  SDL_Surface* surface = TTF_RenderUTF8_Blended(obj->value, text, fg);
  CMemory* mem = cobject_getCMemory((CObject*)obj);
  return initCImageFromSDLSurface(newCImage(mem), surface);
}
