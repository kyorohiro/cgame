#include <stdio.h>
#include "app/capp.h"


int main(int argc, char** argv) {
  printf("test");
  CApp* appObj = getCApp();
  capp_run(appObj);
  return 0;
}
