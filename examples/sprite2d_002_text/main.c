#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "game/ccamera3d.h"
#include "matrix/cmatrix.h"
#include "app/capp.h"
#include "app/cttf.h"
#include "core/cobject.h"
#include "sprite2d/csprite2d.h"
#include "sprite2d/ctext2d.h"

int i =(180+2)%360;
int j =(30+2)%360;
int fps;
CObject3D* sprite001;

void _onEnterFrame(CObject*  obj, CObject* cgame) {
  i =(i+1)%360;

  CApp* appObj = getCApp();
  if(fps != appObj->fps) {
    fps = appObj->fps;
    printf("#fps:%d;\r\n",fps);
  }

  CGame* gameObj = getCGame();
  cgame_postRedisplay(gameObj);
}


int main(int argc, char** argv) {
  printf("call main\r\n");
  //
  CGame* gameObj = createCGame(400, 300);
  cgame_setOnEnterFrameFunc(gameObj, _onEnterFrame);
  //

  CTtf* ttf = cttfMgr_createTtf(getCTtfMgr(), "examples/assets/Roboto-Bold.ttf", 12);
  CDynaTexAtlas* atlas = cgame_getCDynaTexAtlas(gameObj, 0);
  CDynaBlockSpace out;
  ctexAtlas_addImageFromCTtf(atlas, ttf, "testtest", 1.0, 0.5, 0.5, 1.0, &out);
  sprite001 = (CObject3D*)createCText2D(50, 100, atlas, "testtest");

  printf("call main A\r\n");
  //
  CObject3D* root = cgame_getRoot(gameObj);
  cobject3d_addNode(root, (CObject3D*)sprite001);
  ccamera3d_updateAtPerspective(cgame_getCamera(gameObj),
      0.0, 0.0, 5.0,
      0.0, 0.0, 0.0,
      3.14*45.0/180.0, 400.0/300.0, 0.5, 1000.0);

  cgame_run(gameObj);

  return 0;
}
