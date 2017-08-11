#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "game/ccamera3d.h"
int i =0;

void _onEnterFrame(CObject*  obj, CObject* cgame) {
  CGame* game = (CGame*)cgame;
  i = (i+2)%360;
  CMatrix4 rotYMat;
  cmatrix4_setRotationY(&rotYMat, 3.14*i/180.0);
  CMatrix4 rotZMat;
  cmatrix4_setRotationZ(&rotZMat, 3.14*i/180.0);
  CMatrix4 rotXMat;
  cmatrix4_setRotationX(&rotXMat, 3.14*i/180.0);

  CMatrix4 *mat = cobject3d_getCMatrix4((CObject3D*)obj);
//  cmatrix4_setTranslation(initCMatrix4(mat), -2.0, 2.0, -3.0);
  cmatrix4_setTranslation(initCMatrix4(mat), 0.0, 0.0, -3.0);
//  cmatrix4_setTranslation(initCMatrix4(mat), -3.14*i/180.0, 3.14*i/180.0, -3.0);
//  cmatrix4_multiply(&rotYMat, mat, mat);
  cmatrix4_multiply(mat, &rotXMat, mat);
//  cmatrix4_multiply(mat, &rotXMat, mat);
  ccamera3d_update((CCamera3D*)game->camera,
    0.0, 0.0, 5.3,
    0.0, 0.0, 0.0,
//    0.0, 0.0, 3.14*i/180.0,
    3.14*90.0/180.0, 1.0, 0.5, 1000.0);

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
