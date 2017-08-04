#include <stdio.h>
#include "core/cmemory.h"
#include "cmatrix4.h"

int test01();
int main(int argv, char** argc) {
  printf("hello world");
  test01();
  return 0;
}

int test01() {
  CMatrix4 *mat = initCMatrix4(newCMatrix4());
  return 0;
}
