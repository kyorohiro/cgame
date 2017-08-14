#include <stdio.h>
#include "cevent.h"
#include "cmemory.h"

void cevent_test(){
  printf("# cevent_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CEventDispatcher *eve = initCEventDispatcher(newCEventDispatcher(mem));

  //
  //



  releaseCObject((CObject*)eve);
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
