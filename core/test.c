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
    printf("%d %s\n", i, obj->objects[i]->name);
  }
  printf("\n");
  return 0;
}
