#ifndef _H_LINKEDLIST
#define _H_LINKEDLIST
#include "cobject.h"
#include "clinkedList.h"

#define CLINKEDLIST_NAME "lli"
//
// LinkedList
//
typedef struct {
  CObject* value;
  void* next;
  void* prev;
} CLinkedListItem;

typedef struct {
  CObject parent;
  int length;
  int currentIndex;
  CLinkedListItem *begin;
  CLinkedListItem *current;
  CLinkedListItem *end;
} CLinkedList;

CLinkedList* newLinkedList(CMemory* cmemory);
CLinkedList* initLinkedList(CLinkedList *obj);
void freeLinkedList(void* obj);

CObject* linkedList_get(CLinkedList* obj, int index);
CLinkedListItem* linkedList_getItem(CLinkedList* obj, int index);
CObject* linkedList_insert(CLinkedList* obj, CObject *item, int index);
int linkedList_remove(CLinkedList* obj, int index);

CObject* linkedList_getLast(CLinkedList* obj);
CObject* linkedList_addLast(CLinkedList* obj, CObject *item);
int linkedList_removeLast(CLinkedList* obj);

#endif
