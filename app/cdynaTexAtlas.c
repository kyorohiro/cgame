#include "cdynaTexAtlas.h"
#include <stdio.h>

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

CDynaTexAtlas* ctexAtlas_clear(CDynaTexAtlas* obj) {
  cimage_clear(obj->image);
  cdynaBlock_resetIndex(obj->block);
  return obj;
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

int _ctexAtlas_addImageFromSDLSurface(CDynaTexAtlas* obj, SDL_Surface* value, CDynaBlockSpace* out, int isTtf);

int ctexAtlas_addImageFromSDLSurface(CDynaTexAtlas* obj, SDL_Surface* value, CDynaBlockSpace* out) {
  return _ctexAtlas_addImageFromSDLSurface(obj, value, out, 0);
}

int _ctexAtlas_addImageFromSDLSurface(CDynaTexAtlas* obj, SDL_Surface* value, CDynaBlockSpace* out, int isTtf){
  int sw = value->w;
  int sh = value->h;
  int ret = cdynaBlock_findSpace(obj->block, sw, sh, out);
  if(ret == 0) {
    printf("failed to find space %d %d %d %d\r\n", out->x, out->y, out->w, out->h);
    return ret;
  }
  //printf("passed to find space %d %d %d %d: %d %d\r\n", out->x, out->y, out->w, out->h, cimage_getWidth(obj->image), cimage_getHeight(obj->image));

  //
  cdynaBlock_updateIndex(obj->block, out);
  if(isTtf == 0) {
    cimage_updateFromSDLSurface(obj->image, out->x, out->y, out->w, out->h,
        value, 0, 0, sw, sh);
  } else {
    cimage_updateFromSDLSurface2(obj->image, out->x, out->y, out->w, out->h,
        value, 0, 0, sw, sh);
  }
  //
  return 1;
}

int ctexAtlas_addImageFromCTtf(CDynaTexAtlas* obj, CTtf* ttf, char *text, double r, double g, double b, double a, CDynaBlockSpace* out) {
  SDL_Surface* value = cttf_createSDLSurfaceAtSolid(ttf, text, r, g, b, a);
  if(value == NULL) {
    return 0;
  }
#ifdef CIMAGE_USE_DISPLAY_FORMAT
  SDL_SetAlpha(value, 0, SDL_ALPHA_TRANSPARENT);
  //value = SDL_DisplayFormat(value);
  //SDL_DisplayFormatAlpha
#endif
  int ret = _ctexAtlas_addImageFromSDLSurface(obj, value, out, 1);
  SDL_FreeSurface(value);
  return ret;
}

int ctexAtlas_addImageFromPath(CDynaTexAtlas* obj, char* path, CDynaBlockSpace* out) {
  SDL_Surface* value = cimageUtil_loadFromPath( path );
  if(value == NULL) {
    printf("failed to load image %s\r\n", path);
    return 0;
  }
  printf("passed to load image %s\r\n", path);
  int ret = ctexAtlas_addImageFromSDLSurface(obj, value, out);
  printf("passed to load image %d %d %d %d\r\n", out->x, out->y, out->w, out->h);
  SDL_FreeSurface(value);
  return ret;
}

CImage* ctexAtlas_getImage(CDynaTexAtlas* obj) {
  return obj->image;
}

int ctexAtlas_getWidth(CDynaTexAtlas* obj) {
  return cimage_getWidth(obj->image);
}
int ctexAtlas_getHeight(CDynaTexAtlas* obj) {
  return cimage_getHeight(obj->image);
}
