#ifndef _H_CSTRING
#define _H_CSTRING
//typedef int (*free)(int n);

#include "cmemory.h"
#include "object.h"


#define COBJECT_MODE_FREEABLE 0x01
#define COBJECT_NAME "obj";

// UTF8
typedef struct {
  CObject parent;
  char* value;
  int length;
  int byteLength;
} CString;

CString* newCString(CMemory*);
CString* initCString(CString* obj, const char *name, char *value);

#endif
