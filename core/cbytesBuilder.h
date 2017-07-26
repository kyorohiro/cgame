#ifndef _H_BYTESBUILDER
#define _H_BYTESBUILDER

#include "cmemory.h"
#include "cobject.h"
#include "clinkedList.h"

#define CBYTESBUILDER_NAME "obj"

// UTF8
typedef struct {
  CObject parent;
  CLinkedList* values;
} CBytesBuilder;

CBytesBuilder* newCBytesBuilder(CMemory*);
CBytesBuilder* initCBytesBuilder(CBytesBuilder* obj);
CBytesBuilder* cbytesBuilder_addChars(CBytesBuilder* obj, char* v, int length);
#endif
