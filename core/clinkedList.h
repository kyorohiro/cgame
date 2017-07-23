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

CLinkedList* newCLinkedList(CMemory* cmemory);
CLinkedList* initCLinkedList(CLinkedList *obj);

CObject* clinkedList_get(CLinkedList* obj, int index);
CLinkedListItem* clinkedList_getItem(CLinkedList* obj, int index);
CObject* clinkedList_insert(CLinkedList* obj, CObject *item, int index);
int clinkedList_remove(CLinkedList* obj, int index);

CObject* clinkedList_getLast(CLinkedList* obj);
CObject* clinkedList_addLast(CLinkedList* obj, CObject *item);
int clinkedList_removeLast(CLinkedList* obj);

#endif
