#include "cttf.h"
#include <stdio.h>
#include <SDL_opengl.h>

CTtfMgr* newCTtfMgr(CMemory* mem);
CTtfMgr* initCTtfMgr(CTtfMgr* obj);
CTtf* newCTtf(CMemory* mem);
CTtf* initCTtf(CTtf* obj, char* path);

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
