#ifndef _H_CSTRING
#define _H_CSTRING
//typedef int (*free)(int n);

#include "cmemory.h"
#include "cobject.h"


#define CSTRING_NAME "str"

// UTF8
typedef struct {
  CObject parent;
  char* value;
  int length;
  int byteLength;
} CString;

CString* newCString(CMemory*);
CString* initCString(CString* obj, char *value);

#endif
