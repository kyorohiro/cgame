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

LinkedList* initLinkedList(LinkedList *obj, const char *name) {
  initCObject((CObject*)obj, name);
  obj->length = 0;
  obj->parent.funcFreeObj = freeLinkedList;
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
      printf("_%d,",i);
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
  printf("#ZX3C %d %d %d\n",
  obj->parent.cmemory->callocCounter,
  obj->parent.cmemory->freeCounter,
  item->reference);

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
//
// ArrayList
//
ArrayList* newArrayList(CMemory* cmemory) {
  ArrayList* ret =  cmemory_calloc(cmemory,1, sizeof(ArrayList));
  ret->parent.cmemory = cmemory;
  return ret;
}

ArrayList* initArrayList(ArrayList *obj, const char *name, int max) {
  initCObject((CObject*)obj, name);
  obj->length = 0;
  obj->max = max;
  obj->objects = (CObject**) cmemory_calloc(obj->parent.cmemory,max, sizeof(CObject*));
  obj->parent.funcFreeObj = freeArrayList;
  return obj;
}

void freeArrayList(void* obj) {
  if(obj == NULL) {
    return;
  }
  ArrayList *arrayListObj = (ArrayList *)obj;
  if(arrayListObj->objects != NULL) {
    cmemory_free(arrayListObj->parent.cmemory,arrayListObj->objects);
  }
  freeCObject(obj);
}

ArrayList* arrayList_grow(ArrayList* obj) {
  CObject**tmp = obj->objects;
  int tmpMax = obj->max;
  int max = tmpMax;
  int i = 0;
  obj->objects = cmemory_calloc(obj->parent.cmemory,max, sizeof(CObject));
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
