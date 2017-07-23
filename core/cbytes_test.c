#include <stdio.h>
#include "cbytes.h"
#include "cmemory.h"

void cbytes_test(){
  printf("# cbytes_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CBytes *bye = initCBytes(newCBytes(mem), "abc", 4);

  if(cbyte_getLength(bye) != 4) {
    printf("  NG : length = %d\r\n", cbyte_getLength(bye));
    passed = 0;
  }

  char *v = cbyte_getBytes(bye);
  if(v[0] != 'a' || v[1] != 'b' || v[2] != 'c' || v[3] != '\0') {
    printf("  NG : value = %s\r\n", cbyte_getBytes(bye));
    passed = 0;
  }

  releaseCObject((CObject*)bye);
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
