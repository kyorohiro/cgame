#include <stdio.h>
#include <string.h>
#include "core/cmemory.h"
#include "core/clinkedList.h"
#include "core/cbytes.h"
#include "cobject3d.h"
#include "croot3d.h"

void croot3d_test(){
  printf("croot3d_test\r\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CRoot3D *bye = initCRoot3D(newCRoot3D(mem), 10);

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
