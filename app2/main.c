#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"

int main(int argc, char** argv) {
  printf("test");
  CGame* gameObj = getCGame();
  CObject3D *root = cgame_getRoot(gameObj);
  CObject3D *cube = initCObject3DAsCube(newCObject3D(getCMemory()));
  cmatrix4_setRotationZ(cube->mat, 3.14/180*20);

  cobject3d_addNode(root, cube);
  cgame_start(gameObj);
  return 0;
}
