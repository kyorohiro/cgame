#include "cobjectManager.h"
#include <stdlib.h>
#include <stdio.h>
#include "carrayList.h"

void freeCObjectManager(void* obj);
CObjectManager* newCObjectManager(CMemory *mem) {
  CObjectManager *ret = calloc(1,sizeof(CObjectManager));
  ret->parent.cmemory = mem;
  return ret;
}

CObjectManager* initCObjectManager(CObjectManager *obj) {
  initCObject((CObject *)obj, CObjectManager_NAME);
  obj->objects = initCArrayList(newCArrayList(obj->parent.cmemory), 15);
  obj->parent.funcFree = freeCObjectManager;
  return obj;
}

CObjectManager* createCObjectManager() {
  return initCObjectManager(newCObjectManager(getCMemory()));
}

void freeCObjectManager(void* obj) {
  free(((CObjectManager*)obj)->objects);
  freeCObject((CObject*)obj);
}

CObjectManager* cobjectManager_addObject(CObjectManager *obj, CObject *item) {
  carrayList_addLast(obj->objects, item);
  cobject_offMode(item, COBJECT_MODE_FREEABLE);
  item->index = obj->objects->length;
  return obj;
}

CObjectManager* cobjectManager_releaseAll(CObjectManager *obj) {
  int i = 0;
  for(i=0;i<obj->objects->length;i++) {
    CObject *tmp = obj->objects->objects[i];
    if(tmp == NULL) {
      continue;
    }
    if(tmp->reference <=0) {
      releaseCObject(tmp);
      carrayList_set(obj->objects, i, NULL);
    }
  }
  return obj;
}

CObjectManager* cobjectManager_releaseObject(CObjectManager *obj, CObject *item) {
  int index = item->index-1;
  cobject_onMode(item, COBJECT_MODE_FREEABLE);
  carrayList_set(obj->objects, index, NULL);
  return obj;
}

CObjectManager* cobjectManager_showInfo(CObjectManager *obj) {
  int i=0;
  printf("length:%d \n", obj->objects->length);
  for(i=0;i<obj->objects->length;i++) {
    CObject* item = carrayList_get(obj->objects, i);
    if(item != NULL) {
      printf("[%d] %d:%s;r:%d; \n", i, item->index, item->name, item->reference);
    } else {
      printf("[%d] NULL; \n", i);
    }
  }
  return obj;
}

CObjectManager* defaultCObjectManager = NULL;

CObjectManager* getCObjectManager() {
  if(defaultCObjectManager == NULL) {
      defaultCObjectManager = initCObjectManager(newCObjectManager(getCMemory()));
  }
  return defaultCObjectManager;
}
