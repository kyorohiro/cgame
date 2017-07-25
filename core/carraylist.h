#ifndef _H_CArrayList
#define _H_CArrayList
#include "cobject.h"

#define CCArrayList_NAME "ali"

//
// CArrayList
//
typedef struct {
  CObject parent;
  int max;
  int length;
  CObject **objects;
} CArrayList;

CArrayList* newCArrayList(CMemory* cmemory);
CArrayList* initCArrayList(CArrayList *obj, int max);
CArrayList* CArrayList_addLast(CArrayList* obj, CObject *item);
CArrayList* CArrayList_removeLast(CArrayList* obj);
CObject* CArrayList_getLast(CArrayList* obj);
CObject* CArrayList_get(CArrayList* obj, int index);
CArrayList* CArrayList_set(CArrayList* obj, int index, CObject *item);

CArrayList* CArrayList_grow(CArrayList* obj);
#endif
