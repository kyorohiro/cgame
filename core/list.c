#include "object.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include "cmemory.h"

//
// LinkedList
//

LinkedList* newLinkedList(CMemory* cmemory) {
  LinkedList* ret = cmemory_calloc(cmemory, 1, sizeof(LinkedList));
  ret->parent.cmemory = cmemory;
  return ret;
}

LinkedList* initLinkedList(LinkedList *obj) {
  initCObject((CObject*)obj, LINKEDLIST_NAME);

  obj->length = 0;
  obj->parent.funcFree = freeLinkedList;
  obj->begin = (LinkedListItem*)cmemory_calloc(obj->parent.cmemory, 1, sizeof(LinkedListItem));
  obj->end = (LinkedListItem*)cmemory_calloc(obj->parent.cmemory, 1, sizeof(LinkedListItem));
  ((LinkedListItem*)obj->begin)->next = obj->end;
  ((LinkedListItem*)obj->end)->prev = obj->begin->next;
  return obj;
}

void freeLinkedList(void* obj) {
  if(obj == NULL) {
    return;
  }
  LinkedList *linkedListObj = (LinkedList *)obj;
  while(linkedListObj->length > 0)
  {
      linkedList_removeLast(linkedListObj);
  }

  cmemory_free(linkedListObj->parent.cmemory, linkedListObj->begin);
  cmemory_free(linkedListObj->parent.cmemory, linkedListObj->end);
  linkedListObj->begin = NULL;
  linkedListObj->end = NULL;
  freeCObject(obj);
}

LinkedListItem* linkedList_getItem(LinkedList* obj, int index) {
  int i=0;
  LinkedListItem *cur =NULL;
  if(!(0<=index && index<obj->length)){
    return NULL;
  }
  if(index < obj->length/2) {
    cur = obj->begin;
    for(i=0;i<=index;i++) {
      cur = cur->next;
    }
  } else {
    cur = obj->end;
    for(i=obj->length-1;i>=index;i--) {
      cur = cur->prev;
    }
  }
  return cur;
}

CObject* linkedList_get(LinkedList* obj, int index) {
  LinkedListItem *cur = linkedList_getItem(obj, index);
  if(cur == NULL) {
    return NULL;
  }
  return cur->value;
}

CObject* linkedList_insert(LinkedList* obj, CObject *item, int index) {
  LinkedListItem *cur = linkedList_getItem(obj, index);

  LinkedListItem *newItem;
  LinkedListItem *curNext;

  if(cur == NULL ) {
    if(index == 0) {
      cur = obj->begin;
    }
    else if(index == obj->length) {
      cur = obj->end->prev;
    }
    else {
      return NULL;
    }
  }
  newItem = cmemory_calloc(obj->parent.cmemory,1, sizeof(LinkedListItem));

  newItem->value = item;
  newItem->value->reference++;

  curNext = cur->next;
  cur->next = newItem;
  newItem->prev = cur;
  curNext->prev = newItem;
  newItem->next = curNext;
  obj->length++;
  return item;
}

int linkedList_remove(LinkedList* obj, int index) {
  LinkedListItem *item = linkedList_getItem(obj, index);
  if(item == NULL) {
    return -1;
  }
  LinkedListItem *cur = item->prev;
  LinkedListItem *curNext = item->next;
  cur->next = curNext;
  curNext->prev = cur;
  if(item->value != NULL) {
    releaseCObject((CObject*)item->value);
  }
  obj->length--;
  cmemory_free(obj->parent.cmemory,item);

  return 1;
}

CObject* linkedList_getLast(LinkedList* obj) {
  return linkedList_get(obj, obj->length-1);
}

CObject* linkedList_addLast(LinkedList* obj, CObject *item) {
  return linkedList_insert(obj, item, obj->length);
}

int linkedList_removeLast(LinkedList* obj) {
  return linkedList_remove(obj, obj->length-1);
}
