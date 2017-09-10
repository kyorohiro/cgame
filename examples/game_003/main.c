#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "game/ccamera3d.h"
#include "matrix/cmatrix.h"
#include "matrix/cmatrix4.h"
#include "matrix/cmatrix_proj.h"

#include "app/capp.h"
#include "core/cobject.h"

int main(int argc, char** argv) {
  printf("call main");

  CGame* gameObj = getCGame();
  CObject3D *root = cgame_getRoot(gameObj);
  CObject3D *cube1 = (CObject3D*)initCPrimitive3DAsTriangle(newCPrimitive3D(getCMemory()));
  CObject3D *square1 = (CObject3D*)initCPrimitive3DAsSquare(newCPrimitive3D(getCMemory()));
  cmatrix4_setTranslation(cobject3d_getCMatrix4((CObject3D*)cube1), 0.0, 0.0, 0.0);
//  cobject3d_addNode(root, cube1);
  cobject3d_addNode(root, square1);
  ccamera3d_update(cgame_getCamera(gameObj),
      0.0, 0.0, 5.0,
      0.0, 0.0, 0.0,
      3.14*45.0*0.5/180.0, 400.0/300.0, 0.5, 100.0);

  cgame_start(gameObj);

  return 0;
}
