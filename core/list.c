#include "object.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

//
// LinkedList
//

LinkedList* newLinkedList() {
  return calloc(1, sizeof(LinkedList));
}

LinkedList* initLinkedList(LinkedList *obj, const char *name) {
  initCObject((CObject*)obj, name);
  obj->length = 0;
  obj->parent.funcFreeObj = freeLinkedList;
  obj->begin = (LinkedListItem*)calloc(1, sizeof(LinkedListItem));
  obj->end = (LinkedListItem*)calloc(1, sizeof(LinkedListItem));
  ((LinkedListItem*)obj->begin)->next = obj->end;
  ((LinkedListItem*)obj->end)->prev = obj->begin->next;
  return obj;
}

void freeLinkedList(void* obj) {
  if(obj == NULL) {
    return;
  }
  LinkedList *linkedListObj = (LinkedList *)obj;
//  if(arrayListObj->objects != NULL) {
//    free(arrayListObj->objects);
//  }
  free(linkedListObj->begin);
  free(linkedListObj->end);
  linkedListObj->begin = NULL;
  linkedListObj->end = NULL;
  freeCObject(obj);
}

CObject* linkedList_get(LinkedList* obj, int index) {
  int i=0;
  if(!(0<=index && index<obj->length)){
    return NULL;
  }
  LinkedListItem *cur = obj->begin;
  for(i=0;i<=index;i++) {
    cur = cur->next;
  }
  return cur->value;
}

LinkedList* linkedList_addLast(LinkedList* obj, CObject *item) {
  LinkedListItem *newItem = calloc(1,sizeof(LinkedList));
  newItem->value = item;
  return obj;
}

LinkedList* linkedList_removeLast(LinkedList* obj) {
  return NULL;
}
//
// ArrayList
//
ArrayList* newArrayList() {
  return calloc(1, sizeof(ArrayList));
}

ArrayList* initArrayList(ArrayList *obj, const char *name, int max) {
  initCObject((CObject*)obj, name);
  obj->length = 0;
  obj->max = max;
  obj->objects = (CObject**) calloc(max, sizeof(CObject*));
  obj->parent.funcFreeObj = freeArrayList;
  return obj;
}

void freeArrayList(void* obj) {
  if(obj == NULL) {
    return;
  }
  ArrayList *arrayListObj = (ArrayList *)obj;
  if(arrayListObj->objects != NULL) {
    free(arrayListObj->objects);
  }
  freeCObject(obj);
}

ArrayList* arrayList_grow(ArrayList* obj) {
  CObject**tmp = obj->objects;
  int tmpMax = obj->max;
  int max = tmpMax;
  int i = 0;
  obj->objects = calloc(max, sizeof(CObject));
  for(i=0;i<obj->length;i++) {
    obj->objects[i] = tmp[i];
  }
  return obj;
}

ArrayList* arrayList_addLast(ArrayList* obj, CObject *item) {
  if(obj->length+1 >= obj->max) {
    arrayList_grow(obj);
  }
  obj->objects[obj->length++] = item;
  return obj;
}

ArrayList* arrayList_removeLast(ArrayList* obj) {
  if(obj->length<=0) {
    return obj;
  }
  arrayList_set(obj, obj->length, NULL);
  obj->length--;
  return obj;
}

CObject* arrayList_getLast(ArrayList* obj) {
  if(obj->length<=0) {
    return NULL;
  }
  return obj->objects[--obj->length];
}

CObject* arrayList_get(ArrayList* obj, int index) {
  if(obj->length>=index) {
    return NULL;
  }
  return obj->objects[index];
}

ArrayList* arrayList_set(ArrayList* obj, int index, CObject *item) {
  if(obj->length <= index) {
    return obj;
  }

  CObject *tmp = obj->objects[index];
  if(tmp != NULL) {
    obj->objects[index] = NULL;
    tmp->reference--;
  }
  obj->objects[index] = item;
  if(item != NULL) {
    item->reference++;
  }
  return obj;
}
