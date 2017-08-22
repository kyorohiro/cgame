#ifndef _H_CEXCEPT
#define _H_CEXCEPT
//typedef int (*free)(int n);

#include "cmemory.h"
#include "cobject.h"
#include "clinkedList.h"
#include <setjmp.h>

#define CEXCEPT_NAME "cex"
//#define CTry {if(0 == cexception_start(getCException()))
#define CTry {if(0 == setjmp( getCException()->env_buffer ))
#define CCatch else
#define CEnd }
//#define CEnd

typedef struct {
  CObject parent;
  jmp_buf value;
} CJmpBuffer;

CJmpBuffer* newCJmpBuffer(CMemory* cmemory);
CJmpBuffer* initCJmpBuffer(CJmpBuffer* obj);


typedef struct {
  CObject parent;
  CLinkedList *stack;
  jmp_buf env_buffer;
} CException;

CException* newCException(CMemory*);
CException* initCException(CException*);
CException* getCException();

int cexception_start(CException* obj);
void cexception_throw(CException* obj, CObject* arg);
CObject* cexception_end(CException* obj);
#endif
