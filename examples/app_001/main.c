#include <stdio.h>
#include "app/capp.h"


int main(int argc, char** argv) {
  printf("test");
  CApp* appObj = getCApp();
  capp_start(appObj);
  return 0;
}
