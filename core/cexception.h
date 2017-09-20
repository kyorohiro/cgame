#ifndef _H_CException
#define _H_CException

#include "ccore_inner.h"
#include "cmemory.h"
#include "cobject.h"
#include "clinkedList.h"
#include <setjmp.h>


//
#define CTry if(0 == setjmp(cexception_addLast(getCException())->value))
#define CCatch else if(1 == cexception_rmLast(getCException()))
#define CThrow(aa) cexception_throw(getCException(), aa)

//
#define CTryA(aa) if(0 == setjmp(cexception_addLast(aa)->value))
#define CCatchA(aa) else if(1 == cexception_rmLast(aa))
#define CThrowA(aa,bb) cexception_throw(aa, bb)

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
