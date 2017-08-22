#ifndef _H_CEXCEPT
#define _H_CEXCEPT
//typedef int (*free)(int n);

#include "cmemory.h"
#include "cobject.h"
#include "clinkedList.h"


#define CEXCEPT_NAME "cex"

typedef struct {
  CObject parent;
  CLinkedList *stack;
} CException;

CException* newCException(CMemory*);
CException* initCException(CException*);

/*CException* getCException();
void cexception_start(CException* );
void cexception_throw(CException* ,int kind);
void cexception_catch(CException* ,int kind);
void cexception_end(CException* );
*/
#endif
