#include "cimage.h"
#include <stdio.h>
#include <SDL_opengl.h>

CImageMgr* newCImageMgr(CMemory* mem);
CImageMgr* initCImageMgr(CImageMgr* obj);
CImage* initCImageFromPath(CImage* obj, char* path);


CImageMgr* defaultCImageMgr = NULL;
CImageMgr* getCImageMgr() {
  if(defaultCImageMgr == NULL) {
    defaultCImageMgr = initCImageMgr(newCImageMgr(getCMemory()));
  }
  return defaultCImageMgr;
}

CImage* cimageMgr_createImage(CImageMgr* obj, char* path) {
  CMemory* cmemory = cobject_getCMemory((CObject*)obj);
  CImage* ret = initCImageFromPath(newCImage(cmemory), path);
  return ret;
}

void _freeCImage(void* obj) {
  CObject *objObj = (CObject*)obj;
  CImage *imgObj = (CImage*)obj;
  if(imgObj != NULL) {
    SDL_FreeSurface(imgObj->value);
    imgObj->value = NULL;
  }
  freeCObject(obj);
}

void _freeCImageMgr(void* obj) {
  CObject *objObj = (CObject*)obj;
  CImageMgr *imgMgrObj = (CImageMgr*)obj;
  IMG_Quit();
  freeCObject(obj);
}

CImageMgr* newCImageMgr(CMemory* cmemory) {
  CImageMgr* ret = (CImageMgr*)cmemory_calloc(cmemory, 1, sizeof(CImageMgr));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCImageMgr;
  return ret;
}

CImageMgr* initCImageMgr(CImageMgr* obj) {
  initCObject((CObject*)obj, CIMAGE_MGR_NAME);
  int imgFlags = IMG_INIT_PNG;
  if(imgFlags != IMG_Init( imgFlags )){
    printf( "Failed at IMGE_Init %s\n", IMG_GetError() );
  }
  return obj;
}

CImage* newCImage(CMemory* cmemory) {
  CImage* ret = (CImage*)cmemory_calloc(cmemory, 1, sizeof(CImage));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCImage;
  return ret;
}

CImage* initCImageFromPath(CImage* obj, char* path){
  initCObject((CObject*)obj, CIMAGE_NAME);
  SDL_Surface* value = IMG_Load( path );
  obj->value = value;
  return obj;
}

CImage* initEmptyRPGACImage(CImage* obj, int w, int h) {
  initCObject((CObject*)obj, CIMAGE_NAME);
  SDL_Surface* value = SDL_CreateRGBSurface(
    SDL_SWSURFACE, w, h, 32,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
     0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF
#else
     0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
#endif
   );
  obj->value = value;
  return obj;
}

CImage* createEmptyRPGACImage(int w, int h) {
  return initEmptyRPGACImage(newCImage(getCMemory()), w, h);
}

void cimage_update(CImage *dst, int dx, int dy, int dw, int dh,
                    CImage *src, int sx, int sy, int sw, int sh) {
  SDL_Rect s = {.x=sx,.y=sy, .w=sw, .h=sh};
  SDL_Rect d = {.x=dx,.y=dy, .w=dw, .h=dh};
  SDL_BlitSurface(src->value, &s, dst->value, &d);
}

CImage* initCImageFromSDLSurface(CImage* obj, SDL_Surface* value) {
  initCObject((CObject*)obj, CIMAGE_NAME);
  obj->value = value;
  return obj;
}

int cimage_getWidth(CImage* obj) {
  return obj->value->w;
}

int cimage_getHeight(CImage* obj) {
  return obj->value->h;
}

void* cimage_getPixels(CImage* obj) {
  return obj->value->pixels;
}

int cimage_getColorFormat(CImage* obj) {
  int nOfColors = obj->value->format->BytesPerPixel;
  int rmask = obj->value->format->Rmask;
  if (nOfColors == 4) {
    if (rmask == 0x000000ff) {
      return CIMAGE_COLOR_FROMAT_RGBA;
    } else {
      return CIMAGE_COLOR_FROMAT_BGRA;
    }
  } else if (nOfColors == 3) {
    if (rmask == 0x000000ff){
      return CIMAGE_COLOR_FROMAT_RGB;
    } else {
      return CIMAGE_COLOR_FROMAT_BGR;
    }
  } else {
    return CIMAGE_COLOR_FROMAT_NONE;
  }
}

int cimage_getColorFormatGL(CImage* obj, int def) {
  int v = cimage_getColorFormat(obj);
  switch (v) {
    case CIMAGE_COLOR_FROMAT_RGBA:
      return GL_RGBA;
    case CIMAGE_COLOR_FROMAT_BGRA:
      return GL_BGRA;
    case CIMAGE_COLOR_FROMAT_RGB:
      return GL_RGB;
    case CIMAGE_COLOR_FROMAT_BGR:
      return GL_BGR;
    default:
      return def;
  }
}
