#ifndef _H_CBYTE
#define _H_CBYTE
//typedef int (*free)(int n);

#include "cmemory.h"
#include "cobject.h"


#define CBYTE_NAME "bys"

// UTF8
typedef struct {
  CObject parent;
  char* value;
  int length;
} CBytes;

CBytes* newCBytes(CMemory*);
CBytes* initCBytes(CBytes* obj, char *value, int length);
int cbyte_getLength(CBytes* obj);
char* cbyte_getBytes(CBytes* obj);
#endif
