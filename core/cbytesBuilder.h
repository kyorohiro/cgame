#ifndef _H_CBytesBuilder
#define _H_CBytesBuilder

#include "ccore_inner.h"
#include "cmemory.h"
#include "cobject.h"
#include "clinkedList.h"
#include "cstring.h"
#include "cbytes.h"


typedef struct {
  CObject parent;
  CLinkedList* values;
  int length;
} CBytesBuilder;

//
CBytesBuilder* newCBytesBuilder(CMemory*);
CBytesBuilder* initCBytesBuilder(CBytesBuilder* obj);
CBytesBuilder* initCBytesBuilderFromPath(CBytesBuilder* obj, char *path);
CBytesBuilder* createCBytesBuilder(CBytesBuilder* obj);
CBytesBuilder* createCBytesBuilderFromPath(CBytesBuilder* obj, char *path);

//
CBytesBuilder* cbytesBuilder_addChars(CBytesBuilder* obj, char* v, int length);
int cbytesBuilder_getLength(CBytesBuilder* obj);
CBytes* cbytesBuilder_newBytes(CBytesBuilder* obj);
CString* cbytesBuilder_newString(CBytesBuilder* obj);

// utill
CString* cutil_newCStringFromPath(CMemory*, char* path);
#endif
