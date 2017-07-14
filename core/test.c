#include <stdio.h>
#include "object.h"
#include "list.h"

int test01();
int test02();

int main(int argv, char** argc) {
  printf("hello world");
  test01();
  test02();
  return 0;
}

int test01() {
  CObject *obj = initCObject(newCObject(),"test object");
  onMode(obj, COBJECT_MODE_FREEABLE);
  printf("%s", obj->name);
  printf("%d", obj->reference);
  releaseCObject(obj);
  printf("%d", obj->reference);
  printf("\n");
  return 0;
}

int test02() {
  ArrayList *obj = initArrayList(newArrayList(), "test list", 10);
  arrayList_addLast(obj, initCObject(newCObject(), "obj00"));
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
