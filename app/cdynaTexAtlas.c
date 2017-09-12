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

int ctexAtlas_addImage(CDynaTexAtlas* obj, CImage *src, int sx, int sy, int sw, int sh, CDynaBlockSpace* out) {
  int ret = cdynaBlock_findSpace(obj->block, sw, sh, out);
  if(ret == 0) {
    return ret;
  }
  //
  cdynaBlock_updateIndex(obj->block, out);
  cimage_update(obj->image, out->x, out->y, out->w, out->h,
      src, sx, sy, sw, sh);
  //
  return 1;
}

int ctexAtlas_addImageManually(CDynaTexAtlas* obj, int dx, int dy, int dw, int dh, CImage *src, int sx, int sy, int sw, int sh) {
  CDynaBlockSpace out;
  out.x = dx;  out.y = dy;  out.w = dw;  out.h = dh;
  cdynaBlock_updateIndex(obj->block, &out);
  cimage_update(obj->image, out.x, out.y, out.w, out.h,
      src, sx, sy, sw, sh);
  return 1;
}
