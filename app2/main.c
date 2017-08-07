#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"


int i =0;
void _onEnterFrame(CObject*  obj, CObject* cgame) {
  i = (i+2)%360;
//  printf("%f,", 3.14*i/180.0);
  cobject3d_setRotate((CObject3D*)obj, 3.14*i/180.0, 3.14*i/180.0, 3.14*i/180.0);
  //cmatrix4_setRotationZ(obj->mat, 3.14/180*20);
}
int main(int argc, char** argv) {
  printf("test");
  CGame* gameObj = getCGame();
  CObject3D *root = cgame_getRoot(gameObj);
  CObject3D *cube = initCObject3DAsCube(newCObject3D(getCMemory()));
  //scmatrix4_setRotationZ(cube->mat, 3.14/180*20);
    cobject3d_setRotate((CObject3D*)cube,  3.14/180.0*30.0,  3.14/180*30,  3.14/180*30);
    //((float*)cube->vertexs->value)[7] = 1.2;
  cube->onEnterFrameFunc =_onEnterFrame;
  printf("xxx");
  cobject3d_addNode(root, cube);
  cgame_start(gameObj);
  return 0;
}
