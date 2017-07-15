#ifndef _H_LIST
#define _H_LIST
#include "object.h"
#include "list.h"


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

LinkedList* newLinkedList();
LinkedList* initLinkedList(LinkedList *obj, const char *name);
void freeLinkedList(void* obj);

CObject* linkedList_get(LinkedList* obj, int index);
LinkedListItem* linkedList_getItem(LinkedList* obj, int index);
int linkedList_insert(LinkedList* obj, CObject *item, int index);
int linkedList_remove(LinkedList* obj, int index);

//
// ArrayList
//
typedef struct {
  CObject parent;
  int max;
  int length;
  CObject **objects;
} ArrayList;

ArrayList* newArrayList();
ArrayList* initArrayList(ArrayList *obj, const char *name, int max);
ArrayList* arrayList_addLast(ArrayList* obj, CObject *item);
ArrayList* arrayList_removeLast(ArrayList* obj);
CObject* arrayList_getLast(ArrayList* obj);
CObject* arrayList_get(ArrayList* obj, int index);
ArrayList* arrayList_set(ArrayList* obj, int index, CObject *item);

void freeArrayList(void* obj);
ArrayList* arrayList_grow(ArrayList* obj);
#endif
