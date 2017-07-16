#include <stdio.h>
#include "object.h"
#include "list.h"
#include "arraylist.h"
#include "cmemory.h"

int test01();
int test02();
int test03a();
int test03b();

int main(int argv, char** argc) {
  printf("hello world");
  test01();
  test02();
  test03a();
  test03b();
  return 0;
}

int test01() {
  CObject *obj = initCObject(newCObject(getCMemory()),"test object");
  onMode(obj, COBJECT_MODE_FREEABLE);
  printf("%s %d \r\n", obj->name, obj->reference);
  releaseCObject(obj);
  printf("mem: expect  %d == %d \n",getCMemory()->callocCounter, getCMemory()->freeCounter);
  return 0;
}

int test02() {
  ArrayList *obj = initArrayList(newArrayList(getCMemory()), "test list", 10);
  arrayList_addLast(obj, downCounter(initCObject(newCObject(getCMemory()), "obj00")));
  arrayList_addLast(obj, downCounter(initCObject(newCObject(getCMemory()), "obj01")));
  printf("\n");
  for(int i=0;i<obj->length;i++) {
    printf("%d %s (%d)\n", i, obj->objects[i]->name,obj->objects[i]->reference);
  }
  /*0
  printf("#%d\n", obj->length);
  for(int i=0;i<obj->length;i++) {
    CObject *tmp = obj->objects[i];
    arrayList_set(obj, i, NULL);
    printf("%d %s (%d)\n", i, tmp->name, tmp->reference);
  }*/
  releaseCObject((CObject*)obj);
  printf("mem: expect  %d == %d \n",getCMemory()->callocCounter, getCMemory()->freeCounter);
  printf("\n");
  return 0;
}

int test03a() {
  LinkedList *obj = initLinkedList(newLinkedList(getCMemory()), "test list");
  offMode((CObject*)obj, COBJECT_MODE_FREEABLE);
  releaseCObject((CObject*)obj);

  if(obj->parent.reference <= 0) {
    releaseForceCObject((CObject*)obj);
  }
  printf("mem: expect  %d == %d \n",getCMemory()->callocCounter, getCMemory()->freeCounter);
  return 0;
}

int test03b() {
  //
  //
  LinkedList *obj = initLinkedList(newLinkedList(getCMemory()), "test list");
  printf("%d", obj->length);
  linkedList_addLast(obj, downCounter(initCObject(newCObject(getCMemory()),"test00")));
  linkedList_addLast(obj, downCounter(initCObject(newCObject(getCMemory()),"test01")));
//  downCounter(o);
//  printf("===%d\n", o->reference);
/*
  printf("[A]%d", obj->length);
  for(int i=0;i<obj->length;i++) {
    printf("%s\r\n", linkedList_get(obj, i)->name);
  }

  linkedList_addLast(obj, downCounter(initCObject(newCObject(getCMemory()),"test01")));
  printf("[B]%d", obj->length);
  for(int i=0;i<obj->length;i++) {
    printf("%s %d \r\n", linkedList_get(obj, i)->name, linkedList_get(obj, i)->reference);
  }

  linkedList_removeLast(obj);
  */
  printf("[C12]%d\r\n", obj->length);
  for(int i=0;i<obj->length;i++) {
    printf("## %s %d \r\n", linkedList_get(obj, i)->name, linkedList_get(obj, i)->reference);
  }
  printf("[ZZZ]\n");
  releaseCObject((CObject*)obj);
  printf("mem: expect  %d == %d \n",getCMemory()->callocCounter, getCMemory()->freeCounter);
//  printf("===%d\n", o->reference);
  return 0;
}
