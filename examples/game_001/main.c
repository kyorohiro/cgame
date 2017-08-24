#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "game/ccamera3d.h"
#include "matrix/cmatrix.h"
#include "app/capp.h"
#include "core/cobject.h"

int i =(20+2)%360;

void _onEnterFrame(CObject*  obj, CObject* cgame) {
  CGame* gameObj = getCGame();
  i = (i+2)%360;
  CMatrix4Raw rotYMat;
  CMatrix4Raw rotZMat;
  CMatrix4Raw rotXMat;

  cmatrix4raw_setRotationX(rotXMat, 3.14*i/180.0);
  cmatrix4raw_setRotationY(rotYMat, 3.14*i/180.0);
  cmatrix4raw_setRotationZ(rotZMat, 3.14*i/180.0);

  CMatrix4 *mat = cobject3d_getCMatrix4((CObject3D*)obj);

  cmatrix4_setTranslation(initCMatrix4(mat), 0.0, 0.0, -2.0);

  cmatrix4raw_mul(rotYMat, mat->value, mat->value);
  cmatrix4raw_mul(mat->value, rotXMat, mat->value);
//  cmatrix4raw_mul(mat->value, rotYMat, mat->value);
//  cmatrix4raw_mul(mat->value, rotZMat, mat->value);


  cgame_postRedisplay(gameObj);
}

int main(int argc, char** argv) {
  printf("call main\r\n");

  CGame* gameObj = getCGame();
  CObject3D *root = cgame_getRoot(gameObj);
  CObject3D *cube1 = (CObject3D*)initCPrimitive3DAsCube(newCPrimitive3D(getCMemory()));
  CObject3D *cube2 = (CObject3D*)initCPrimitive3DAsTriangle(newCPrimitive3D(getCMemory()));

  cube1->onEnterFrameFunc =_onEnterFrame;
  cobject3d_addNode(root, cube1);
  cobject3d_addNode(root, cube2);

  ccamera3d_update(cgame_getCamera(gameObj),
      0.0, 0.0, 5.0,
      0.0, 0.0, 0.0,
      3.14*45.0/180.0, 400.0/300.0, 0.5, 1000.0);

  cgame_start(gameObj);

  return 0;
}
