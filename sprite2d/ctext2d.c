#include "csprite2d.h"
#include "ctext2d.h"
#include <stdio.h>

void freeCText2D(void* obj) {
  CText2D* objTmp = obj;
  if(objTmp->text == NULL) {
    releaseCObject((CObject*)objTmp->text);
  }
  freeCSprite2D(obj);
}

CText2D* newCText2D(CMemory* mem) {
  CText2D* ret = cmemory_calloc(mem, 1, sizeof(CText2D));
  ((CObject*)ret)->cmemory = mem;
  ((CObject*)ret)->funcFree = freeCText2D;
  return ret;
}

CText2D* initCText2D(CText2D* obj, CMatrixVertexType width, CMatrixVertexType height, CDynaTexAtlas* atlas, char *text) {
  CMemory* mem = cobject_getCMemory((CObject*)obj);
  initCSprite2D((CSprite2D*)obj, width, height);
  obj->text = initCString(newCString(mem), text);
  obj->atlas = (CDynaTexAtlas*)cobject_upCounter((CObject*)atlas);
  return obj;
}

CText2D* createCText2D(CMatrixVertexType width, CMatrixVertexType height, CDynaTexAtlas* atlas, char *text) {
  return initCText2D(newCText2D(getCMemory()), width, height, atlas, text);
}
