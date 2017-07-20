#include <stdio.h>
#include "core/cmemory.h"
#include "glmatrix.h"

int test01();
int main(int argv, char** argc) {
  printf("hello world");
  test01();
  return 0;
}

int test01() {
  KMatrix *mat = initKMatrix(newKMatrix());
  return 0;
}
