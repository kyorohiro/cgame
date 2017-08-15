#include <stdio.h>
#include "cevent.h"
#include "cmemory.h"
#include "cstring.h"

void _testOnEvent(CObject* context, CObject* args){

}
void cevent_test(){
  printf("# cevent_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CEventDispatcher *eve = initCEventDispatcher(newCEventDispatcher(mem));

  //
  //
  CObject *context = (CObject*)initCString(newCString(mem), "abc");
  cobject_downCounter(context);
  CEventObserver* ob = ceventDispatcher_addListener(eve, context, _testOnEvent);
  ceventDispatcher_removeListener(eve, ob);

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
