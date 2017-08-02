#ifndef _H_BYTESBUILDER
#define _H_BYTESBUILDER

#include "cmemory.h"
#include "cobject.h"
#include "cbytes.h"
#include "cstring.h"
#include "clinkedList.h"

#define CBYTESBUILDER_NAME "obj"

// UTF8
typedef struct {
  CObject parent;
  CLinkedList* values;
  int length;
} CBytesBuilder;

CBytesBuilder* newCBytesBuilder(CMemory*);
CBytesBuilder* initCBytesBuilder(CBytesBuilder* obj);
CBytesBuilder* cbytesBuilder_addChars(CBytesBuilder* obj, char* v, int length);
int cbytesBuilder_getLength(CBytesBuilder* obj);
CBytes* cbytesBuilder_newBytes(CBytesBuilder* obj);
CString* cbytesBuilder_newString(CBytesBuilder* obj);
// utill
CBytesBuilder* initCBytesBuilderFromPath(CBytesBuilder* obj, char *path);

CString* cutil_newCStringFromPath(CMemory*, char* path);
#endif
