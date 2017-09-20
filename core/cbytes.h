#ifndef _H_CBytes
#define _H_CBytes

#include "ccore_inner.h"
#include "cmemory.h"
#include "cobject.h"


typedef struct {
  CObject parent;
  char* value;
  int length;
} CBytes;

CBytes* newCBytes(CMemory*);
CBytes* initCBytes(CBytes* obj, char *value, int length);
CBytes* createCBytes(char *value, int length);

int cbytes_getLength(CBytes* obj);
char* cbytes_getBytes(CBytes* obj);
CBytes* cbytes_setLength(CBytes* obj, int nextlength);

#endif
