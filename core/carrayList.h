#ifndef _H_CArrayList
#define _H_CArrayList

#include "ccore_inner.h"
#include "cobject.h"

typedef struct {
  CObject parent;
  int max;
  int length;
  CObject **objects;
} CArrayList;

CArrayList* newCArrayList(CMemory* cmemory);
CArrayList* initCArrayList(CArrayList *obj, int max);
CArrayList* createCArrayList(int max);

CArrayList* carrayList_openAll(CArrayList *obj);
CArrayList* carrayList_addLast(CArrayList* obj, CObject *item);
CArrayList* carrayList_removeLast(CArrayList* obj);
CObject* carrayList_getLast(CArrayList* obj);
CObject* carrayList_get(CArrayList* obj, int index);
CArrayList* carrayList_set(CArrayList* obj, int index, CObject *item);
CArrayList* carrayList_grow(CArrayList* obj);
int carrayList_getLength(CArrayList* obj);
#endif
