#include <stdio.h>
#include <string.h>
#include "cmemory.h"
#include "clinkedList.h"

void clinkedList_test(){
  printf("# clinkedList_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CLinkedList *lin = initCLinkedList(newCLinkedList(mem));

  if(clinkedList_getLength(lin) != 0) {
    printf("  NG : length = %d\r\n", clinkedList_getLength(lin));
    passed = 0;
  }

  clinkedList_addLast(lin, cobject_downCounter(initCObject(newCObject(mem), "test1")));
  clinkedList_addLast(lin, cobject_downCounter(initCObject(newCObject(mem), "test2")));
  clinkedList_insert(lin, cobject_downCounter(initCObject(newCObject(mem), "test")),1);

  if(clinkedList_getLength(lin) != 3) {
    printf("  NG1 : length = %d\r\n", clinkedList_getLength(lin));
    passed = 0;
  }

  if(strcmp(clinkedList_get(lin,0)->name, "test1") != 0) {
    printf("  NG2 %s: \r\n", clinkedList_get(lin,0)->name);
    passed = 0;
  }

  if(strcmp(clinkedList_get(lin,1)->name, "test") != 0) {
    printf("  NG3_2 %s: \r\n",clinkedList_get(lin,2)->name);
    printf("  NG3_1 %s: \r\n", clinkedList_get(lin,1)->name);
    printf("  NG3_0 %s: \r\n", clinkedList_get(lin,0)->name);
    passed = 0;
  }

  if(strcmp(clinkedList_get(lin,2)->name, "test2") != 0) {
    printf("  NG4 : \r\n");
    passed = 0;
  }

  clinkedList_remove(lin, 0);
  if(clinkedList_getLength(lin) != 2) {
    printf("  NG5 : length = %d\r\n", clinkedList_getLength(lin));
    passed = 0;
  }

  if(strcmp(clinkedList_get(lin,0)->name, "test") != 0) {
    printf("  NG6_1 %s: \r\n", clinkedList_get(lin,1)->name);
    printf("  NG6_0 %s: \r\n", clinkedList_get(lin,0)->name);
    passed = 0;
  }


  releaseCObject((CObject*)lin);
  if(mem->callocCounter != mem->freeCounter) {
    printf("  NG : %d == %d\r\n", mem->callocCounter, mem->freeCounter);
    passed = 0;
  }

  freeCMemory(mem);
  if(passed) {
    printf("  OK : \r\n");
  }
  printf("\r\n\r\n");
}
