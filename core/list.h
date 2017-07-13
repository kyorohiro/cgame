#ifndef _H_LIST
#define _H_LIST
#include "object.h"


typedef struct {
  CObject parent;
  int max;
  int length;
  CObject **objects;
} ArrayList;

ArrayList* newArrayList();
ArrayList* initArrayList(ArrayList *obj, const char *name, int max);
ArrayList* add(ArrayList* obj, CObject *item);
void freeArrayList(void* obj);
#endif
