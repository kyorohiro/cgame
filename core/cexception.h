#ifndef _H_CEXCEPT
#define _H_CEXCEPT
//typedef int (*free)(int n);

#include "cmemory.h"
#include "cobject.h"
#include "clinkedList.h"
#include <setjmp.h>

#define CEXCEPT_NAME "cex"
//
#define CTry if(0 == setjmp(cexception_addLast(getCException())->value))
#define CCatch else if(1 == cexception_rmLast(getCException()))
//
#define CTryA(aa) if(0 == setjmp(cexception_addLast(aa)->value))
#define CCatchA(aa) else if(1 == cexception_rmLast(aa))


typedef struct {
  CObject parent;
  jmp_buf value;
} CJmpBuffer;

CJmpBuffer* newCJmpBuffer(CMemory* cmemory);
CJmpBuffer* initCJmpBuffer(CJmpBuffer* obj);


typedef struct {
  CObject parent;
  CLinkedList *stack;
  CObject *current;
} CException;

CException* newCException(CMemory*);
CException* initCException(CException*);
CException* getCException();

CJmpBuffer* cexception_addLast(CException* obj);
CJmpBuffer* cexception_getLast(CException* obj);
int cexception_rmLast(CException* obj);
void cexception_throw(CException* obj, CObject* arg);
CObject* cexception_end(CException* obj);
#endif
