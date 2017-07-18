#include <stdio.h>
#include "game/cgame.h"

int main(int argc, char** argv) {
  printf("test");
  CGame* gameObj = getCGame();
  cgame_start(gameObj);
  return 0;
}
