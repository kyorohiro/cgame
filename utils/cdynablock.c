#include "cdynablock.h"

void _freeCDynaBlock(void* obj) {
  CObject* objObj = (CObject*)obj;
  CDynaBlock* byeObj = (CDynaBlock*)obj;
  freeCObject(obj);
}

CDynaBlock* newCDynaBlock(CMemory* cmemory) {
  CDynaBlock* ret = cmemory_calloc(cmemory, 1, sizeof(CDynaBlock));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCDynaBlock;
}

CDynaBlock* initCDynaBlock(CDynaBlock* obj) {
  return obj;
}