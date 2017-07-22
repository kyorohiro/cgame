#ifndef _H_BYTESBUILDER
#define _H_BYTESBUILDER

#include "cmemory.h"
#include "object.h"
#include "list.h"

#define BYTESBUILDER_NAME "obj"

// UTF8
typedef struct {
  CObject parent;
  LinkedList* values;
} BytesBuilder;

BytesBuilder* newBytesBuilder(CMemory*);
BytesBuilder* initBytesBuilder(BytesBuilder* obj);

#endif
