#include "cimage.h"

void _freeCImage(void* obj) {
  CObject *objObj = (CObject*)obj;
  CImage *imgObj = (CImage*)obj;
  if(imgObj == NULL) {
    SDL_FreeSurface(imgObj->value);
    imgObj->value = NULL;
  }
  freeCObject(obj);
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
