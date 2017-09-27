#include <stdio.h>
#include "cdynablock.h"


void dynaBlock_test_a();
void dynaBlock_test_b();
void dynaBlock_test_c();

int main(int argc, char** argv) {
  dynaBlock_test_a();
  dynaBlock_test_b();
  dynaBlock_test_c();
}


void dynaBlock_test_c() {
  printf("# dynaBlock_test_c\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CDynaBlock *objBlock = initCDynaBlock(newCDynaBlock(mem), 100, 100);

  CDynaBlockSpace out;
  int ret;
  cdynaBlock_show(objBlock);
  printf(">60,20\r\n");
  ret = cdynaBlock_findSpace(objBlock, 60, 20, &out);
  cdynaBlock_updateIndex(objBlock, &out);
  if(ret != 1 || out.w != 60 || out.h != 20 || out.x != 0 || out.y != 0) {
    printf("  NG a: %d : %d %d %d %d\r\n", ret, out.x, out.y, out.w, out.h);
    passed = 0;
  }
  cdynaBlock_show(objBlock);

  printf(">50,10\r\n");
  ret = cdynaBlock_findSpace(objBlock, 50, 10, &out);
  cdynaBlock_updateIndex(objBlock, &out);
  if(ret != 1 || out.w != 50 || out.h != 10 || out.x != 0 || out.y != 20) {
    printf("  NG b: %d : %d %d %d %d\r\n", ret, out.x, out.y, out.w, out.h);
    passed = 0;
  }
  cdynaBlock_show(objBlock);

  printf(">10,80\r\n");
  ret = cdynaBlock_findSpace(objBlock, 10, 80, &out);
  cdynaBlock_updateIndex(objBlock, &out);
  if(ret != 1 || out.w != 10 || out.h != 80 || out.x != 60 || out.y != 0) {
    printf("  NG b: %d : %d %d %d %d\r\n", ret, out.x, out.y, out.w, out.h);
    passed = 0;
  }
  cdynaBlock_show(objBlock);


  printf(">30,20\r\n");
  ret = cdynaBlock_findSpace(objBlock, 30, 20, &out);
  cdynaBlock_updateIndex(objBlock, &out);
  if(ret != 1 || out.w != 30 || out.h != 20 || out.x != 70 || out.y != 0) {
    printf("  NG c: %d : %d %d %d %d\r\n", ret, out.x, out.y, out.w, out.h);
    passed = 0;
  }
  cdynaBlock_show(objBlock);


  printf(">90,10\r\n");
  ret = cdynaBlock_findSpace(objBlock, 90, 10, &out);
  cdynaBlock_updateIndex(objBlock, &out);
  if(ret != 1 || out.w != 90 || out.h != 10 || out.x != 0 || out.y != 80) {
    printf("  NG d: %d : %d %d %d %d\r\n", ret, out.x, out.y, out.w, out.h);
    passed = 0;
  }
  cdynaBlock_show(objBlock);

  printf(">40,40\r\n");
  ret = cdynaBlock_findSpace(objBlock, 40, 40, &out);

  if(ret != 0) {
    printf("  NG e: %d : %d %d %d %d\r\n", ret, out.x, out.y, out.w, out.h);
    passed = 0;
  }

  //
  //
  releaseCObject((CObject*)objBlock);
  if(mem->callocCounter != mem->freeCounter) {
    printf("  NG : %d == %d\r\n", mem->callocCounter, mem->freeCounter);
    passed = 0;
  }

  freeCMemory(mem);
  if(passed) {
    printf("  OK : \r\n");
  }
  return;
}

void dynaBlock_test_b() {
  printf("# dynaBlock_test_b\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CDynaBlock *objBlock = initCDynaBlock(newCDynaBlock(mem), 100, 100);

  CDynaBlockSpace out;
  int ret;

  printf(">40,40\r\n");
  ret = cdynaBlock_findSpace(objBlock, 40, 40, &out);
  cdynaBlock_updateIndex(objBlock, &out);
  if(ret != 1 || out.w != 40 || out.h != 40 || out.x != 0 || out.y != 0) {
    printf("  NG a: %d : %d %d %d %d\r\n", ret, out.x, out.y, out.w, out.h);
    passed = 0;
  }
  cdynaBlock_show(objBlock);

  printf(">40,40\r\n");
  ret = cdynaBlock_findSpace(objBlock, 40, 40, &out);
  cdynaBlock_updateIndex(objBlock, &out);
  if(ret != 1 || out.w != 40 || out.h != 40 || out.x != 40 || out.y != 0) {
    printf("  NG b: %d : %d %d %d %d\r\n", ret, out.x, out.y, out.w, out.h);
    passed = 0;
  }
  cdynaBlock_show(objBlock);

  printf(">40,40\r\n");
  ret = cdynaBlock_findSpace(objBlock, 40, 40, &out);
  cdynaBlock_updateIndex(objBlock, &out);
  if(ret != 1 || out.w != 40 || out.h != 40 || out.x != 0 || out.y != 40) {
    printf("  NG c: %d : %d %d %d %d\r\n", ret, out.x, out.y, out.w, out.h);
    passed = 0;
  }
  cdynaBlock_show(objBlock);


  printf(">40,40\r\n");
  ret = cdynaBlock_findSpace(objBlock, 40, 40, &out);
  cdynaBlock_updateIndex(objBlock, &out);
  if(ret != 1 || out.w != 40 || out.h != 40 || out.x != 40 || out.y != 40) {
    printf("  NG d: %d : %d %d %d %d\r\n", ret, out.x, out.y, out.w, out.h);
    passed = 0;
  }
  cdynaBlock_show(objBlock);

  printf(">40,40\r\n");
  ret = cdynaBlock_findSpace(objBlock, 40, 40, &out);
  if(ret != 0) {
    printf("  NG e: %d \r\n", ret);
    passed = 0;
  }
  //
  //
  releaseCObject((CObject*)objBlock);
  if(mem->callocCounter != mem->freeCounter) {
    printf("  NG : %d == %d\r\n", mem->callocCounter, mem->freeCounter);
    passed = 0;
  }

  freeCMemory(mem);
  if(passed) {
    printf("  OK : \r\n");
  }
  return;
}

void dynaBlock_test_a() {
  printf("# dynaBlock_test_a\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CDynaBlock *objBlock = initCDynaBlock(newCDynaBlock(mem), 100, 100);
  releaseCObject((CObject*)objBlock);

  if(mem->callocCounter != mem->freeCounter) {
    printf("  NG : %d == %d\r\n", mem->callocCounter, mem->freeCounter);
    passed = 0;
  }

  freeCMemory(mem);
  if(passed) {
    printf("  OK : \r\n");
  }
  return;
}
