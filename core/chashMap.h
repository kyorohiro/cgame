
#ifndef _H_HASHMAP
#define _H_HASHMAP
#include "cobject.h"
#include "clinkedList.h"
#include "carrayList.h"

#define CHASHMAP_NAME "hma"


typedef struct {
  CObject parent;
  CArrayList *index;
} CHashMap;

CHashMap* newCHashMap(CMemory* cmemory);
CHashMap* initCHashMap(CHashMap *obj);

#endif
