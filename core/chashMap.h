
#ifndef _H_HASHMAP
#define _H_HASHMAP
#include "cobject.h"
#include "clinkedList.h"
#include "carrayList.h"

#define CHASHMAP_NAME "hma"
#define CHASHMAP_ITEM_NAME "hmi"

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
CObject* chashMap_get(CHashMap *obj, CObject *key);

#endif
