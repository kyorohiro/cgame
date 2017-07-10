#include "object.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

ArrayList* newArrayList(const char *name, int max) {
  ArrayList *obj = calloc(1, sizeof(ArrayList));
  initObject((CObject*)obj, name);
  obj->length = 0;
  obj->max = max;
  obj->objects = calloc(max, sizeof(CObject));
  return obj;
}
