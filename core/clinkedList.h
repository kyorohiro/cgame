#ifndef _H_CLinkedListItem
#define _H_CLinkedListItem

#include "ccore_inner.h"
#include "cmemory.h"
#include "cobject.h"
#include "clinkedList.h"


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
CLinkedList* createCLinkedList();

CObject* clinkedList_get(CLinkedList* obj, int index);
CLinkedListItem* clinkedList_getItem(CLinkedList* obj, int index);
CObject* clinkedList_insert(CLinkedList* obj, CObject *item, int index);
int clinkedList_remove(CLinkedList* obj, int index);

CObject* clinkedList_getLast(CLinkedList* obj);
CObject* clinkedList_addLast(CLinkedList* obj, CObject *item);
int clinkedList_removeLast(CLinkedList* obj);
int clinkedList_getLength(CLinkedList* obj);
#endif
