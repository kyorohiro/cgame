#include <stdio.h>
#include "object.h"

int main(int argv, char** argc) {
  printf("hello world");
  CObject *obj = initCObject(newCObject(),"test object");
  printf("%s", obj->name);
  releaseCObject(obj);
  return 0;
}
