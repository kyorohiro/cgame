#include "cdynablock.h"
#include <stdio.h>

void _freeCDynaBlock(void* obj) {
  CObject* objObj = (CObject*)obj;
  CDynaBlock* dynObj = (CDynaBlock*)obj;
  if(dynObj->spaces != NULL) {
    CMemory *cmemory = cobject_getCMemory((CObject*)obj);
    cmemory_free(cmemory, dynObj->spaces);
  }
  freeCObject(obj);
}

CDynaBlock* newCDynaBlock(CMemory* cmemory) {
  CDynaBlock* ret = cmemory_calloc(cmemory, 1, sizeof(CDynaBlock));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCDynaBlock;
  return ret;
}

CDynaBlock* initCDynaBlock(CDynaBlock* obj, int w, int h) {
  CMemory *cmemory = cobject_getCMemory((CObject*)obj);
  initCObject((CObject*)obj, CDYNABLOCK_NAME);
  obj->width = w;
  obj->height = h;
  obj->maxOfSpace = 100;
  obj->numOfSpace = 0;
  obj->spaces = (CDynaBlockSpace*)cmemory_calloc(cmemory, 1, sizeof(CDynaBlockSpace)*obj->maxOfSpace);
  obj->MIN = 1;
  //
  //
  obj->spaces[0].x = 0;
  obj->spaces[0].y = 0;
  obj->spaces[0].w = w;
  obj->spaces[0].h = h;
  obj->numOfSpace = 1;
  return obj;
}

CDynaBlock* createCDynaBlock(int w, int h) {
  return initCDynaBlock(newCDynaBlock(getCMemory()), w, h);
}

int cdynaBlock_findSpace(CDynaBlock* obj, int w, int h, CDynaBlockSpace *out) {
  return 1;
}
