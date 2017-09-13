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

SDL_Surface* cimageUtil_loadFromPath(char *path) {
  SDL_Surface* value = IMG_Load( path );
#ifdef CIMAGE_USE_DISPLAY_FORMAT
  value = SDL_DisplayFormat(value);
#endif
  return value;
}

CImage* initCImageFromPath(CImage* obj, char* path){
  initCObject((CObject*)obj, CIMAGE_NAME);
  obj->value = cimageUtil_loadFromPath( path );
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
  char* buff = obj->value->pixels;

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

void cimage_updateFromSDLSurface(CImage *dst, int dx, int dy, int dw, int dh,
                    SDL_Surface* src, int sx, int sy, int sw, int sh) {
    SDL_Rect s = {.x=sx,.y=sy, .w=sw, .h=sh};
    SDL_Rect d = {.x=dx,.y=dy, .w=dw, .h=dh};

#ifdef CIMAGE_USE_MANUALL_COPY
#ifndef CIMAGE_UNUSE_SCREEN_LOCK
    SDL_LockSurface(src);
#endif
#endif

#ifdef CIMAGE_USE_MANUALL_COPY
    unsigned char *x = dst->value->pixels;
    unsigned char *y = src->pixels;
    printf("srcx %d %d : %d %d %d: %d %d %d %d \r\n", src->w,src->h, src->pitch,
        src->format->BitsPerPixel,
        dst->value->format->BytesPerPixel,
        dst->value->format->Rmask,
        dst->value->format->Gmask,
        dst->value->format->Bmask,
        dst->value->format->Amask
      );
    printf("dstx %d %d : %d %d %d: %d %d %d %d :\r\n", dst->value->w, dst->value->h, dst->value->pitch,
        dst->value->format->BitsPerPixel,
        dst->value->format->BytesPerPixel,
        dst->value->format->Rmask,
        dst->value->format->Gmask,
        dst->value->format->Bmask,
        dst->value->format->Amask
      );
    for(int i=0;i<src->w;i++) {
      for(int j=0;j<src->h;j++) {
        x[4 * (j * dst->value->w + i)+0] = y[4 * (j * src->w + i)+0];
        x[4 * (j * dst->value->w + i)+1] = y[4 * (j * src->w + i)+1];
        x[4 * (j * dst->value->w + i)+2] = 0.9*y[4 * (j * src->w + i)+2];
        x[4 * (j * dst->value->w + i)+3] = 255;//y[4 * (j * src->w + i)+3];
      }
    }
#else
    SDL_BlitSurface(src, &s, dst->value, &d);
#endif
#ifdef CIMAGE_USE_MANUALL_COPY
#ifndef CIMAGE_UNUSE_SCREEN_LOCK
    SDL_UnlockSurface(src);
#endif
#endif

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

int cimage_getColorFormatFromSDLSurface(SDL_Surface* value) {
  int nOfColors = value->format->BytesPerPixel;
  int rmask = value->format->Rmask;
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
