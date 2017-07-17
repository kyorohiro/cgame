#include <stdio.h>
#include "game/cgame.h"

int main(int argc, char** argv) {
  printf("test");
  CGame* gameObj = initCGame(
    newCGame(getCMemory()),
    "game",
    "title",
    300,
    200);

  cgame_start(gameObj);
  return 0;
}
