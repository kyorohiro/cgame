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
ArrayList* arrayList_addLast(ArrayList* obj, CObject *item);
ArrayList* arrayList_removeLast(ArrayList* obj);
CObject* arrayList_getLast(ArrayList* obj);
void freeArrayList(void* obj);
ArrayList* arrayList_grow(ArrayList* obj);
#endif
