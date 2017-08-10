#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"

int i =0;

void _onEnterFrame(CObject*  obj, CObject* cgame) {
  i = (i+2)%360;
  CMatrix4 rotYMat;
  cmatrix4_setRotationY(&rotYMat, 3.14*i/180.0);

  CMatrix4 rotXMat;
  cmatrix4_setRotationX(&rotXMat, 3.14*i/180.0);

  //cmatrix4_setTranslation(initCMatrix4(&transMat), 0.5, 0.5, 0.5);
  CMatrix4 *mat = cobject3d_getCMatrix4((CObject3D*)obj);
//  cmatrix4_setRotationZ(mat, 3.14*i/180.0);
//  cmatrix4_outer(&transMat, mat, mat);
  cmatrix4_setTranslation(initCMatrix4(mat), 0.0, 0.0, -3.6*2);
  //cmatrix4_outer(&rotYMat, mat, mat);
  cmatrix4_outer(mat, &rotXMat, mat);
//  cprimitive3d_setRotate((CPrimitive3D*)obj, 3.14*i/180.0, 3.14*i/180.0, 3.14*i/180.0);
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
