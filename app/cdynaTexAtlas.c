#include "cdynaTexAtlas.h"

void _freeCDynaTexAtlas(void* obj) {
  CObject *objObj = (CObject*)obj;
  CDynaTexAtlas *texObj = (CDynaTexAtlas*)obj;
  if(texObj->image != NULL) {
    releaseCObject((CObject*)texObj->image);
  }
  if(texObj->block != NULL) {
    releaseCObject((CObject*)texObj->block);
  }

  freeCObject(obj);
}

CDynaTexAtlas* newCDynaTexAtlas(CMemory* cmemory) {
  CDynaTexAtlas* ret = (CDynaTexAtlas*)cmemory_calloc(cmemory, 1, sizeof(CDynaTexAtlas));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCDynaTexAtlas;
  return ret;
}

CDynaTexAtlas* initCDynaTexAtlas(CDynaTexAtlas* obj, int w, int h) {
  CMemory* mem = cobject_getCMemory((CObject*)obj);
  initCObject((CObject*)obj, CTEX_ATLAS_NAME);
  obj->image = initEmptyRPGACImage(newCImage(mem), w, h);
  obj->block = initCDynaBlock(newCDynaBlock(mem), w, h);
  return obj;
}

CDynaTexAtlas* createCDynaTexAtlas(int w, int h) {
  return initCDynaTexAtlas(newCDynaTexAtlas(getCMemory()), w, h);
}

TexAtlasBlockRaw ctexAtlas_updateImage(CDynaTexAtlas* obj, int dx, int dy, int dw, int dh, CImage *src, int sx, int sy, int sw, int sh) {
  TexAtlasBlockRaw ret;

  return ret;
}
