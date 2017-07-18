#include "objectManager.h"
#include <stdlib.h>
#include <stdio.h>
#include "arraylist.h"

CObjectManager* newCObjectManager(CMemory *mem) {
  CObjectManager *ret = calloc(1,sizeof(CObjectManager));
  ret->parent.cmemory = mem;
  return ret;
}

CObjectManager* initCObjectManager(CObjectManager *obj, const char *name) {
  obj->objects = initArrayList(newArrayList(obj->parent.cmemory), "", 15);
  snprintf(obj->parent.name, sizeof(obj->parent.name), "%s_objs",name);
  obj->parent.funcFree = freeCObjectManager;
  return obj;
}

void freeCObjectManager(void* obj) {
  free(((CObjectManager*)obj)->objects);
  freeCObject((CObject*)obj);
}

CObjectManager* objectManager_addObject(CObjectManager *obj, CObject *item) {
  arrayList_addLast(obj->objects, item);
  return obj;
}

CObjectManager* objectManager_releaseAll(CObjectManager *obj) {
  int i = 0;
  for(i=0;i<obj->objects->length;i++) {
    CObject *tmp = obj->objects->objects[i];
    if(tmp == NULL) {
      continue;
    }
    if(tmp->reference <=0) {
      releaseCObject(tmp);
      arrayList_set(obj->objects, i, NULL);
    }
  }
  return obj;
}
