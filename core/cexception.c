#include "cexception.h"
#include <stdio.h>

void _freeCException(void* obj) {
  CObject *objObj = (CObject*)obj;
  CException *exeObj = (CException*)obj;
  freeCObject((CObject*)exeObj->stack);
  freeCObject(obj);
}

CException* newCException(CMemory* cmemory) {
  CException* ret = cmemory_calloc(cmemory, 1, sizeof(CException));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCException;
  return ret;
}

CException* initCException(CException* obj) {
  initCObject((CObject *)obj, CEXCEPT_NAME);
  CMemory* cmemory = cobject_getCMemory((CObject *)obj);
  obj->stack = initCLinkedList(newCLinkedList(cmemory));
  return obj;
}

CException* getCException() {
  return NULL;
}

void cexception_start(CException* obj) {

}

void cexception_throw(CException* obj,int kind) {

}

void cexception_catch(CException* obj,int kind) {

}

void cexception_end(CException* obj) {

}
