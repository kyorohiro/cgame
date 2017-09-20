#include <stdio.h>
#include "cbytesBuilder.h"
#include "cmemory.h"
#include "cstring.h"

void cbytesBuilder_test(){
  printf("# cbytesBuilder_test\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CBytesBuilder *bye = initCBytesBuilder(newCBytesBuilder(mem));
  cbytesBuilder_addChars(bye, "abc", 3);
  cbytesBuilder_addChars(bye, "def", 4);

  if(cbytesBuilder_getLength(bye) != 7) {
    printf("  NG : length = %d\r\n", cbytesBuilder_getLength(bye));
    passed = 0;
  }

  CBytes *v = cbytesBuilder_newBytes(bye);
  if(
    v->value[0] != 'a' || v->value[1] != 'b' || v->value[2] != 'c' ||
    v->value[3] != 'd' || v->value[4] != 'e' || v->value[5] != 'f' ||
    v->value[6] != '\0') {
    printf("  NG : value = %s\r\n", cbytes_getBytes(v));
    passed = 0;
  }
  releaseCObject((CObject*)v);
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

void cbytesBuilder_test2(){
  printf("# cbytesBuilder_test2\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CBytesBuilder *bye = initCBytesBuilderFromPath(newCBytesBuilder(mem), "./core/assets/test.dat");

  CBytes *v = cbytesBuilder_newBytes(bye);
  if(
    v->value[0] != 'a' || v->value[1] != 'b' || v->value[2] != 'c' ||
    v->value[3] != 'd' || v->value[4] != 'e' || v->value[5] != 'f'
   || v->value[6] != '\n') {
    printf("  NG : value = %s\r\n", cbytes_getBytes(v));
    passed = 0;
  }
  printf(">>d>>%d<<", bye->length);
  releaseCObject((CObject*)v);

  CString *s = cbytesBuilder_newString(bye);

  if(cstring_getLength(s) != 7 || cstring_getByteLength(s) != 7) {
    printf("  NG : length = %d %d\r\n", cstring_getLength(s),cstring_getByteLength(s));
  }
  releaseCObject((CObject*)s);
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
