#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "game/ccamera3d.h"
#include "matrix/cmatrix.h"
#include "matrix/cmatrix4.h"
#include "matrix/cmatrix_proj.h"

#include "app/capp.h"
#include "app/cimage.h"
#include "core/cobject.h"

int main(int argc, char** argv) {
  printf("call main");
  CGame* gameObj = getCGame();
  cgame_init(gameObj);

  //
  CImageMgr* mgr = getCImageMgr();
  CDynaTexAtlas* atlas = cgame_getCDynaTexAtlas(gameObj, 0);
  CDynaBlockSpace out;
  ctexAtlas_addImageFromPath(atlas, "./examples/assets/icon.png", &out);

  //
  CObject3D *square1 = (CObject3D*)initCPrimitive3DAsSquare(newCPrimitive3D(getCMemory()));
  cmatrix4_setTranslation(cobject3d_getCMatrix4((CObject3D*)square1), 0.0, 0.0, 0.0);
  cprimitive3d_setCImage((CPrimitive3D*)square1, ctexAtlas_getImage(atlas));


  CObject3D *root = cgame_getRoot(gameObj);
  cobject3d_addNode(root, square1);
  ccamera3d_update(cgame_getCamera(gameObj),
      0.0, 0.0, 5.0,
      0.0, 0.0, 0.0,
      3.14*45.0*0.5/180.0, 400.0/300.0, 0.5, 100.0);

  cgame_loop(gameObj);
  return 0;
}
