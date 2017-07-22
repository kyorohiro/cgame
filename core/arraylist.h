#ifndef _H_ARRAYLIST
#define _H_ARRAYLIST
#include "cobject.h"

#define ARRAYLIST_NAME "ali"

//
// ArrayList
//
typedef struct {
  CObject parent;
  int max;
  int length;
  CObject **objects;
} ArrayList;

ArrayList* newArrayList(CMemory* cmemory);
ArrayList* initArrayList(ArrayList *obj, int max);
ArrayList* arrayList_addLast(ArrayList* obj, CObject *item);
ArrayList* arrayList_removeLast(ArrayList* obj);
CObject* arrayList_getLast(ArrayList* obj);
CObject* arrayList_get(ArrayList* obj, int index);
ArrayList* arrayList_set(ArrayList* obj, int index, CObject *item);

ArrayList* arrayList_grow(ArrayList* obj);
#endif
