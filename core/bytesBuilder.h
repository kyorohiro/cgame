#ifndef _H_BYTESBUILDER
#define _H_BYTESBUILDER

#include "cmemory.h"
#include "cobject.h"
#include "clinkedList.h"

#define BYTESBUILDER_NAME "obj"

// UTF8
typedef struct {
  CObject parent;
  CLinkedList* values;
} BytesBuilder;

BytesBuilder* newBytesBuilder(CMemory*);
BytesBuilder* initBytesBuilder(BytesBuilder* obj);
BytesBuilder* bytesBuilder_addChars(BytesBuilder* obj, char* v, int length);
#endif
