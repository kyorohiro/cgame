#include "objectManager.h"
#include <stdlib.h>
#include <stdio.h>

CObjectManager* newCObjectManager() {
  CObjectManager *ret = calloc(1,sizeof(CObjectManager));
  return ret;
}

CObjectManager* initCObjectManager(CObjectManager *obj, const char *name) {
  obj->objects = initArrayList(newArrayList(), "", 15);
  snprintf(obj->parent.name, sizeof(obj->parent.name), "%s_objs",name);
  obj->parent.funcFreeObj = freeCObjectManager;
  return obj;
}

void freeCObjectManager(void* obj) {
  free(((CObjectManager*)obj)->objects);
  freeCObject((CObject*)obj);
}

CObjectManager* objectManager_addObject(CObjectManager *obj, CObject *item) {
//  cA obj->objects
  return NULL;
}
