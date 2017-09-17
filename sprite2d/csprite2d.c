#include "csprite2d.h"
#include <stdio.h>

void freeCSprite2D(void* obj) {
  CSprite2D* objTmp = obj;
  freeCObject3D(obj);
}

CSprite2D* newCSprite2D(CMemory* mem) {
  CSprite2D* ret = cmemory_calloc(mem, 1, sizeof(CSprite2D));
  ret->parent.parent.cmemory = mem;
  ret->parent.parent.funcFree = freeCSprite2D;
  return ret;
}

CSprite2D* initCSprite2D(CSprite2D* obj, int width, int height) {
  initCPrimitive3D((CPrimitive3D*)obj);
  return obj;
}

CSprite2D* createCSprite2D(int width, int height) {
  return initCSprite2D(newCSprite2D(getCMemory()), width, height);
}
