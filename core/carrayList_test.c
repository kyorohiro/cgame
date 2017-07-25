#include <stdio.h>
#include <string.h>
#include "cmemory.h"
#include "carrayList.h"

void carrayList_test(){
  printf("# arrayList_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CArrayList *lin = initCArrayList(newCArrayList(mem),2);

  if(carrayList_getLength(lin) != 0) {
    printf("  NG : length = %d\r\n", carrayList_getLength(lin));
    passed = 0;
  }

  carrayList_addLast(lin, cobject_downCounter(initCObject(newCObject(mem), "test1")));
  carrayList_addLast(lin, cobject_downCounter(initCObject(newCObject(mem), "test2")));
  carrayList_addLast(lin, cobject_downCounter(initCObject(newCObject(mem), "test3")));

  if(carrayList_getLength(lin) != 3) {
    printf("  NG : length = %d\r\n", carrayList_getLength(lin));
    passed = 0;
  }

  if(strcmp(carrayList_get(lin,0)->name, "test1") != 0) {
    printf("  NG2 %s: \r\n", carrayList_get(lin,0)->name);
    passed = 0;
  }

  if(strcmp(carrayList_get(lin,1)->name, "test2") != 0) {
    printf("  NG3_2 %s: \r\n", carrayList_get(lin,2)->name);
    printf("  NG3_1 %s: \r\n", carrayList_get(lin,1)->name);
    printf("  NG3_0 %s: \r\n", carrayList_get(lin,0)->name);
    passed = 0;
  }

  if(strcmp(carrayList_get(lin,2)->name, "test3") != 0) {
    printf("  NG4 : \r\n");
    passed = 0;
  }

  carrayList_set(lin, 0, NULL);
  if(carrayList_getLength(lin) != 3) {
    printf("  NG : length = %d\r\n", carrayList_getLength(lin));
    passed = 0;
  }
  carrayList_removeLast(lin);
  if(carrayList_getLength(lin) != 2) {
    printf("  NG : length = %d\r\n", carrayList_getLength(lin));
    passed = 0;
  }

  if(strcmp(carrayList_get(lin,1)->name, "test2") != 0) {
    printf("  NG6_1 : \r\n");
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
