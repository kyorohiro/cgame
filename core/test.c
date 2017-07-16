#include <stdio.h>
#include "object.h"
#include "list.h"
#include "cmemory.h"

int test01();
int test02();
int test03();
int test03a();

int main(int argv, char** argc) {
  printf("hello world");
  test01();
  test02();
  test03a();
  test03();
  return 0;
}

int test01() {
  CObject *obj = initCObject(newCObject(getCMemory()),"test object");
  onMode(obj, COBJECT_MODE_FREEABLE);
  printf("%s", obj->name);
  printf("%d", obj->reference);
  releaseCObject(obj);
  printf("%d", obj->reference);
  printf("\n");
  return 0;
}

int test02() {
  ArrayList *obj = initArrayList(newArrayList(getCMemory()), "test list", 10);
  arrayList_addLast(obj, initCObject(newCObject(getCMemory()), "obj00"));
  printf("#%d\n", obj->length);
  for(int i=0;i<obj->length;i++) {
    printf("%d %s (%d)\n", i, obj->objects[i]->name,obj->objects[i]->reference);
  }
  printf("#%d\n", obj->length);
  for(int i=0;i<obj->length;i++) {
    CObject *tmp = obj->objects[i];
    arrayList_set(obj, i, NULL);
    printf("%d %s (%d)\n", i, tmp->name, tmp->reference);
  }

  printf("\n");
  return 0;
}

int test03a() {
  //
  //
  LinkedList *obj = initLinkedList(newLinkedList(getCMemory()), "test list");
  releaseCObject((CObject*)obj);


  return 0;
}

int test03() {
  //
  //
  LinkedList *obj = initLinkedList(newLinkedList(getCMemory()), "test list");
  printf("%d", obj->length);
  linkedList_addLast(obj, downCounter(initCObject(newCObject(getCMemory()),"test00")));
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
  printf("[C]%d", obj->length);
  for(int i=0;i<obj->length;i++) {
    printf("%s %d \r\n", linkedList_get(obj, i)->name, linkedList_get(obj, i)->reference);
  }

  return 0;
}
