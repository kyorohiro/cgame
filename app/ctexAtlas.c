#include "ctexAtlas.h"

void _freeCTexAtlas(void* obj) {
  CObject *objObj = (CObject*)obj;
  CTexAtlas *texObj = (CTexAtlas*)obj;
  freeCObject(obj);
}

CTexAtlas* newCTexAtlas(CMemory* cmemory) {
  CTexAtlas* ret = (CTexAtlas*)cmemory_calloc(cmemory, 1, sizeof(CTexAtlas));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCTexAtlas;
  return ret;
}

CTexAtlas* initCTexAtlas(CTexAtlas* obj, int w, int h) {
  CMemory* mem = cobject_getCMemory((CObject*)obj);
  initCObject((CObject*)obj, CTEX_ATLAS_NAME);
  obj->image = initEmptyRPGACImage(newCImage(mem), w, h);
  return obj;
}

CTexAtlas* createCTexAtlas(int w, int h) {
  return initCTexAtlas(newCTexAtlas(getCMemory()), w, h);
}

TexAtlasBlockRaw ctexAtlas_updateImage(CTexAtlas* obj, int dx, int dy, int dw, int dh, CImage *src, int sx, int sy, int sw, int sh) {
  TexAtlasBlockRaw ret;
  
  return ret;
}
