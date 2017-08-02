#include <stdio.h>
#include "cobject.h"
#include "clinkedList.h"
#include "carrayList.h"
#include "cmemory.h"
#include "cobjectManager.h"

extern void cbytes_test();
extern void cstring_test();
extern void clinkedList_test();
extern void carrayList_test();
extern void cbytesBuilder_test();
extern void cbytesBuilder_test2();

int main(int argv, char** argc) {
  CObjectManager *objMgr = getCObjectManager();
  printf("Test Start System : %d == %d \n",
    getCMemory()->callocCounter,
    getCMemory()->freeCounter);

  cbytes_test();
  cstring_test();
  clinkedList_test();
  carrayList_test();
  cbytesBuilder_test();
  cbytesBuilder_test2();

  return 0;
}
