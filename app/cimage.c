#include "cimage.h"
#include <stdio.h>
#include <SDL_opengl.h>

CImageMgr* newCImageMgr(CMemory* mem);
CImageMgr* initCImageMgr(CImageMgr* obj);
CImage* initCImage(CImage* obj, char* path);


CImageMgr* defaultCImageMgr = NULL;
CImageMgr* getCImageMgr() {
  if(defaultCImageMgr == NULL) {
    defaultCImageMgr = initCImageMgr(newCImageMgr(getCMemory()));
  }
  return defaultCImageMgr;
}

CImage* cimageMgr_createImage(CImageMgr* obj, char* path) {
  CMemory* cmemory = cobject_getCMemory((CObject*)obj);
  CImage* ret = initCImage(newCImage(cmemory), path);
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

CImage* initCImage(CImage* obj, char* path){
  initCObject((CObject*)obj, CIMAGE_NAME);
  SDL_Surface* value = IMG_Load( path );
  obj->value = value;
  return obj;
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
