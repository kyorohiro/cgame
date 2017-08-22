#include "cexception.h"
#include <stdio.h>
#include <setjmp.h>


//
//
//
void _freeCJmpBuffer(void* obj) {
  CObject *objObj = (CObject*)obj;
  CJmpBuffer *exeObj = (CJmpBuffer*)obj;
  freeCObject(obj);
}

CJmpBuffer* newCJmpBuffer(CMemory* cmemory) {
  CJmpBuffer* ret = cmemory_calloc(cmemory, 1, sizeof(CJmpBuffer));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCJmpBuffer;
  return ret;
}

CJmpBuffer* initCJmpBuffer(CJmpBuffer* obj) {
  return obj;
}

//
//
//
void _freeCException(void* obj) {
  CObject *objObj = (CObject*)obj;
  CException *exeObj = (CException*)obj;
  releaseCObject((CObject*)exeObj->stack);
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


CException* _defaultCException = NULL;
CException* getCException() {
  if(_defaultCException == NULL) {
    _defaultCException = initCException(newCException(getCMemory()));
  }
  return _defaultCException;
}

CJmpBuffer* cexception_push(CException* obj) {
  CMemory* cmemory = cobject_getCMemory((CObject *)obj);
  clinkedList_addLast(obj->stack, (CObject*)initCJmpBuffer(newCJmpBuffer(cmemory)));
  return (CJmpBuffer*)clinkedList_getLast(obj->stack);
}

CJmpBuffer* cexception_peek(CException* obj) {
  return (CJmpBuffer*)clinkedList_getLast(obj->stack);
}

CJmpBuffer* cexception_pop(CException* obj) {
  CJmpBuffer* ret = (CJmpBuffer*)clinkedList_getLast(obj->stack);
  clinkedList_removeLast(obj->stack);
  return ret;
}

void cexception_throw(CException* obj, CObject* arg) {
  CJmpBuffer* item = (CJmpBuffer*)cexception_peek(obj);
  if(item != NULL) {
    longjmp(item->value, 1);
  } else {
    //exit();
  }
}

CObject* cexception_end(CException* obj) {
  return NULL;
}
