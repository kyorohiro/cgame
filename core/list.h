#ifndef _H_LIST
#define _H_LIST
#include "object.h"

//typedef int (*free)(int n);
typedef CObject *pCObject;
typedef struct {
  CObject parent;
  int max;
  int length;
  CObject **objects;
} ArrayList;

ArrayList* newArrayList(const char *name, int max);
#endif
