#ifndef _H_CEXCEPT
#define _H_CEXCEPT
//typedef int (*free)(int n);

#include "cmemory.h"
#include "cobject.h"
#include "clinkedList.h"


#define CEXCEPT_NAME "cex"
#define CTry if(0 == cexception_start(getCException()))
#define CCatch else
//#define CEnd

typedef struct {
  CObject parent;
  CLinkedList *stack;
} CException;

CException* newCException(CMemory*);
CException* initCException(CException*);
CException* getCException();

int cexception_start(CException* obj);
void cexception_throw(CException* obj, CObject* arg);
CObject* cexception_end(CException* obj);
#endif
