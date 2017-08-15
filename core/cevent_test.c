#include <stdio.h>
#include "cevent.h"
#include "cmemory.h"
#include "cstring.h"

int check = 0;
void _testOnEvent(CObject* context, CObject* args){
  CString *str1 = (CString *)context;
  CString *str2 = (CString *)args;
  printf("%s %s\r\n", str1->value, str2->value);
  check = 1;
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
  //
  CString *str = initCString(newCString(mem), "def");
//    printf("call dispatch VEF a\r\n");
  ceventDispatcher_dispatch(eve, (CObject*)str);
//    printf("call dispatch VEF b\r\n");
  releaseCObject((CObject*)str);

  //
  ceventDispatcher_removeListener(eve, ob);

  releaseCObject((CObject*)eve);

  if(check == 0) {
    printf("  NG : check %d\r\n", check);
    passed = 0;
  }

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
