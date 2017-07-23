#include <stdio.h>
#include "cstring.h"
#include "cmemory.h"

void cstring_test(){
  printf("# cstring_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CString *bye = initCString(newCString(mem), "abc");

  if(cstring_getLength(bye) != 3) {
    printf("  NG : length = %d\r\n", cstring_getLength(bye));
    passed = 0;
  }

  if(cstring_getByteLength(bye) != 3) {
    printf("  NG : byteLength = %d\r\n", cstring_getByteLength(bye));
    passed = 0;
  }

  char *v = cstring_getBytes(bye);
  if(v[0] != 'a' || v[1] != 'b' || v[2] != 'c' || v[3] != '\0') {
    printf("  NG : value = %s\r\n", cstring_getBytes(bye));
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
