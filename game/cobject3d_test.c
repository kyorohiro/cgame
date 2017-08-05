#include <stdio.h>
#include <string.h>
#include "core/cmemory.h"
#include "core/clinkedList.h"
#include "core/cbytes.h"
#include "cobject3d.h"

void cobject3d_test(){
  printf("cobject3d_test\r\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CObject3D *bye = initCObject3D(newCObject3D(mem));

  {
    CObject *o = cobject_downCounter((CObject*)initCObject3D(newCObject3D(mem)));
    cobject3d_addNode(bye, (CObject3D*)o);
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
