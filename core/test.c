#include <stdio.h>
#include "cobject.h"
#include "clinkedList.h"
#include "carrayList.h"
#include "cmemory.h"
#include "objectManager.h"

extern void cbytes_test();
extern void cstring_test();
extern void clinkedList_test();

int test01();
int test02();
int test03a();
int test03b();

int main(int argv, char** argc) {
  CObjectManager *objMgr = getCObjectManager();
  printf("Test Start System : %d == %d \n",
    getCMemory()->callocCounter,
    getCMemory()->freeCounter);

  cbytes_test();
  cstring_test();
  clinkedList_test();
//  test01();
//  test02();
//  test03a();
  //test03b();*/
  return 0;
}

int test01() {
  CObjectManager *objMgr = getCObjectManager();
  CObject *obj = initCObject(newCObject(getCMemory()),"test object");
  objectManager_addObject(objMgr, obj);
  releaseCObject(obj);
  objectManager_showInfo(objMgr);
  objectManager_releaseObject(objMgr, obj);
  objectManager_showInfo(objMgr);
  printf("[TEST]\n");
  printf("mem: expect  %d == %d \n\n",
    getCMemory()->callocCounter,
    getCMemory()->freeCounter);

  return 0;
}

int test02() {
  printf("[TEST02]\n");
  CArrayList *objArray = initCArrayList(newCArrayList(getCMemory()), 10);
  CArrayList_addLast(objArray, cobject_downCounter(initCObject(newCObject(getCMemory()), "obj00")));
  CArrayList_addLast(objArray, cobject_downCounter(initCObject(newCObject(getCMemory()), "obj01")));
  for(int i=0;i<objArray->length;i++) {
    printf("a- %d %s (%d)\n", i, objArray->objects[i]->name,objArray->objects[i]->reference);
  }
  for(int i=0;i<objArray->length;i++) {
    CObject *tmp = objArray->objects[i];
    printf("b- %d %s (%d)\n", i, tmp->name, tmp->reference);
    CArrayList_set(objArray, i, NULL);
  }
  releaseCObject((CObject*)objArray);
  printf("mem: expect  %d == %d \n",
    getCMemory()->callocCounter,
    getCMemory()->freeCounter);
  printf("\n");
  return 0;
}

int test03a() {
  CLinkedList *obj = initCLinkedList(newCLinkedList(getCMemory()));
  printf("[TEST03] %d\n",obj->parent.reference );

//  offMode((CObject*)obj, COBJECT_MODE_FREEABLE);
  releaseCObject((CObject*)obj);
  /*
  if(obj->parent.reference <= 0) {
    releaseForceCObject((CObject*)obj);
  }*/
  printf("mem: expect  %d == %d \n",getCMemory()->callocCounter, getCMemory()->freeCounter);
  return 0;
}

int test03b() {
  //
  //
  CLinkedList *obj = initCLinkedList(newCLinkedList(getCMemory()));
  printf("%d", obj->length);
  clinkedList_addLast(obj, cobject_downCounter(initCObject(newCObject(getCMemory()),"test00")));
  clinkedList_addLast(obj, cobject_downCounter(initCObject(newCObject(getCMemory()),"test01")));
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
    printf("## %s %d \r\n", clinkedList_get(obj, i)->name, clinkedList_get(obj, i)->reference);
  }
  printf("[ZZZ]\n");
  releaseCObject((CObject*)obj);
  printf("mem: expect  %d == %d \n",getCMemory()->callocCounter, getCMemory()->freeCounter);
//  printf("===%d\n", o->reference);
  return 0;
}
