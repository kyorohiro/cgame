#include "cobject.h"
#include "clinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include "cmemory.h"

//
// LinkedList
//
void freeCLinkedList(void* obj);
CLinkedList* newCLinkedList(CMemory* cmemory) {
  CLinkedList* ret = cmemory_calloc(cmemory, 1, sizeof(CLinkedList));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = freeCLinkedList;
  return ret;
}

CLinkedList* initCLinkedList(CLinkedList *obj) {
  initCObject((CObject*)obj, CLinkedList_NAME);
  //obj->parent.funcFree = freeCLinkedList;
  obj->length = 0;
  obj->begin = (CLinkedListItem*)cmemory_calloc(obj->parent.cmemory, 1, sizeof(CLinkedListItem));
  obj->end = (CLinkedListItem*)cmemory_calloc(obj->parent.cmemory, 1, sizeof(CLinkedListItem));
  ((CLinkedListItem*)obj->begin)->next = obj->end;
  ((CLinkedListItem*)obj->end)->prev = obj->begin->next;
  return obj;
}

CLinkedList* createCLinkedList() {
  return initCLinkedList(newCLinkedList(getCMemory()));
}
void freeCLinkedList(void* obj) {
  if(obj == NULL) {
    return;
  }
  CLinkedList *linkedListObj = (CLinkedList *)obj;
  while(linkedListObj->length > 0)
  {
      clinkedList_removeLast(linkedListObj);
  }

  cmemory_free(linkedListObj->parent.cmemory, linkedListObj->begin);
  cmemory_free(linkedListObj->parent.cmemory, linkedListObj->end);
  linkedListObj->begin = NULL;
  linkedListObj->end = NULL;
  freeCObject(obj);
}

CLinkedListItem* clinkedList_getItem(CLinkedList* obj, int index) {
  if(!(0<=index && index<obj->length)){
    return NULL;
  }

  CLinkedListItem *cur =NULL;
  //
  if(obj->current != NULL) {
    if(obj->currentIndex == index) {
      return obj->current;
    }
    else if(obj->currentIndex+1 == index) {
      cur = obj->current->next;
      obj->current = cur;
      obj->currentIndex = index;
      return cur;
    }
    else if(obj->currentIndex-1 == index) {
      cur = obj->current->prev;
      obj->current = cur;
      obj->currentIndex = index;
      return cur;
    }
  }
  //
  //
  if(index < obj->length/2) {
    cur = obj->begin;
    for(int i=0;i<=index;i++) {
      cur = cur->next;
    }
  } else {
    cur = obj->end;
    for(int i=obj->length-1;i>=index;i--) {
      cur = cur->prev;
    }
  }
  obj->current = cur;
  obj->currentIndex = index;
  return cur;
}

CObject* clinkedList_get(CLinkedList* obj, int index) {
  CLinkedListItem *cur = clinkedList_getItem(obj, index);
  if(cur == NULL) {
    return NULL;
  }
  return cur->value;
}

CObject* clinkedList_insert(CLinkedList* obj, CObject *item, int index) {
  CLinkedListItem *cur = clinkedList_getItem(obj, index-1);
  CLinkedListItem *newItem;
  CLinkedListItem *curNext;

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
  newItem = cmemory_calloc(obj->parent.cmemory,1, sizeof(CLinkedListItem));

  newItem->value = item;
  newItem->value->reference++;
  curNext = cur->next;
  cur->next = newItem;
  newItem->prev = cur;
  curNext->prev = newItem;
  newItem->next = curNext;
  obj->length++;

  //
  if(obj->currentIndex >= index) {
    obj->currentIndex++;
  }
  return item;
}

int clinkedList_remove(CLinkedList* obj, int index) {
  CLinkedListItem *item = clinkedList_getItem(obj, index);
  if(item == NULL) {
    return -1;
  }
  CLinkedListItem *cur = item->prev;
  CLinkedListItem *curNext = item->next;
  cur->next = curNext;
  curNext->prev = cur;
  if(item->value != NULL) {
    releaseCObject((CObject*)item->value);
  }
  obj->length--;
  cmemory_free(obj->parent.cmemory,item);
  //
  //
  if(obj->currentIndex == index) {
    obj->current = NULL;
  } else if(obj->currentIndex > index) {
    obj->currentIndex--;
  }
  return 1;
}

CObject* clinkedList_getLast(CLinkedList* obj) {
  return clinkedList_get(obj, obj->length-1);
}

CObject* clinkedList_addLast(CLinkedList* obj, CObject *item) {
  return clinkedList_insert(obj, item, obj->length);
}

int clinkedList_removeLast(CLinkedList* obj) {
  return clinkedList_remove(obj, obj->length-1);
}

int clinkedList_getLength(CLinkedList* obj) {
  return obj->length;
}
