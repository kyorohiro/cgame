
#ifndef _H_HASHMAP
#define _H_HASHMAP
#include "cobject.h"
#include "clinkedList.h"
#include "carrayList.h"

#define CHASHMAP_NAME "hma"


typedef struct {
  CObject parent;
  CObject *key;
  CObject *value;
} CHashMapItem;

typedef struct {
  CObject parent;
  CArrayList *index;
  CLinkedList *cache;
} CHashMap;

CHashMap* newCHashMap(CMemory* cmemory);
CHashMap* initCHashMap(CHashMap *obj, int size);
CHashMapItem* newCHashMapItem(CMemory* cmemory);
CHashMapItem* initCHashMapItem(CHashMapItem *obj, CObject *key, CObject *value);
CHashMap* chashMap_put(CHashMap *obj, CObject *key, CObject *value);
#endif
