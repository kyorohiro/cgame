#ifndef _H_CString
#define _H_CString

#include "ccore_inner.h"
#include "cmemory.h"
#include "cobject.h"


// UTF8
typedef struct {
  CObject parent;
  char* value;
  int length;
  int byteLength;
} CString;

CString* newCString(CMemory*);
CString* initCString(CString* obj, char *value);
CString* initCStringWithLength(CString* obj, char *value, int byteLength);
CString* createCString(char *value);
CString* createCStringWithLength(char *value, int byteLength);

int cstring_getLength(CString* obj);
int cstring_getByteLength(CString* obj);
char* cstring_getBytes(CString* obj);

#endif
