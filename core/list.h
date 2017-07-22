#ifndef _H_LINKEDLIST
#define _H_LINKEDLIST
#include "object.h"
#include "list.h"

#define LINKEDLIST_NAME "lli"
//
// LinkedList
//
typedef struct {
  CObject* value;
  void* next;
  void* prev;
} LinkedListItem;

typedef struct {
  CObject parent;
  int length;
  int currentIndex;
  LinkedListItem *begin;
  LinkedListItem *current;
  LinkedListItem *end;
} LinkedList;

LinkedList* newLinkedList(CMemory* cmemory);
LinkedList* initLinkedList(LinkedList *obj);
void freeLinkedList(void* obj);

CObject* linkedList_get(LinkedList* obj, int index);
LinkedListItem* linkedList_getItem(LinkedList* obj, int index);
CObject* linkedList_insert(LinkedList* obj, CObject *item, int index);
int linkedList_remove(LinkedList* obj, int index);

CObject* linkedList_getLast(LinkedList* obj);
CObject* linkedList_addLast(LinkedList* obj, CObject *item);
int linkedList_removeLast(LinkedList* obj);

#endif
