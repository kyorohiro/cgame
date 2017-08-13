#include <stdio.h>
#include <string.h>
#include "cmemory.h"
#include "chashMap.h"
#include "cstring.h"


void chashMap_test(){
  printf("# chashMap_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CHashMap *map = initCHashMap(newCHashMap(mem), 10);


  CString * key1 = initCString(newCString(mem),"k1");
  CString * key2 = initCString(newCString(mem),"k2");
  CString * abc = initCString(newCString(mem),"abc");
  CString * def = initCString(newCString(mem),"def");

  //chashMap_put(map, cobject_downCounter((CObject*)key1), cobject_downCounter((CObject*)abc));
  chashMap_put(map, cobject_downCounter((CObject*)key2), cobject_downCounter((CObject*)def));
  chashMap_put(map, (CObject*)key1, (CObject*)abc);

  if(((CString*)chashMap_get(map, (CObject*)key1))->value[0] != 'a') {
    printf("  NG : 1 : %s \r\n", ((CString*)chashMap_get(map, (CObject*)key1))->value);
    passed = 0;
  }
  chashMap_put(map, (CObject*)key1, (CObject*)def);
  if(((CString*)chashMap_get(map, (CObject*)key1))->value[0] != 'd') {
    printf("  NG : 1 : %s \r\n", ((CString*)chashMap_get(map, (CObject*)key1))->value);
    passed = 0;
  }
  releaseCObject((CObject*)map);
  //printf(" >>>>>  %d %d\n", ((CObject*)key1)->reference, ((CObject*)key1)->mode);
  releaseCObject((CObject*)key1);
  releaseCObject((CObject*)abc);
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
