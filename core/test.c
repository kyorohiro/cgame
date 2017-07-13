#include <stdio.h>
#include "object.h"

int main(int argv, char** argc) {
  printf("hello world");
  CObject *obj = initCObject(newCObject(),"test object");
  onMode(obj, COBJECT_MODE_FREEABLE);
  printf("%s", obj->name);
  printf("%d", obj->reference);
  releaseCObject(obj);
  printf("%d", obj->reference);

  return 0;
}
