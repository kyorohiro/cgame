#ifndef _H_LIST
#define _H_LIST
#include "object.h"


typedef struct {
  CObject parent;
  int max;
  int length;
  CObject **objects;
} ArrayList;

ArrayList* newArrayList(const char *name, int max);
void* freeArrayList(void* obj);
#endif
