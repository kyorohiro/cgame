#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"

int i =0;

void _onEnterFrame(CObject*  obj, CObject* cgame) {
  i = (i+2)%360;
  cprimitive3d_setRotate((CPrimitive3D*)obj, 3.14*i/180.0, 3.14*i/180.0, 3.14*i/180.0);
//  cprimitive3d_setRotate((CPrimitive3D*)obj, 3.14*i/180.0, 0.0, 0.0);
//  cprimitive3d_setRotate((CPrimitive3D*)obj, 0.0, 3.14*i/180.0, 0.0);
//  cprimitive3d_setRotate((CPrimitive3D*)obj, 0.0, 0.0, 3.14*i/180.0);

}

int main(int argc, char** argv) {
  printf("test");
  CGame* gameObj = getCGame();
  CObject3D *root = cgame_getRoot(gameObj);
  CObject3D *cube = (CObject3D*)initCPrimitive3DAsCube(newCPrimitive3D(getCMemory()));
  cube->onEnterFrameFunc =_onEnterFrame;
  cobject3d_addNode(root, cube);
  cgame_start(gameObj);
  return 0;
}
