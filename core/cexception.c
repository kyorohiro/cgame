#include "cexception.h"
#include <stdio.h>
#include <setjmp.h>

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

jmp_buf env_buffer;
int cexception_start(CException* obj) {
  return setjmp( env_buffer );
}

void cexception_throw(CException* obj, CObject* arg) {

}

CObject* cexception_end(CException* obj) {
  return NULL;
}
