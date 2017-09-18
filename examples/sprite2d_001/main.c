#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "game/ccamera3d.h"
#include "matrix/cmatrix.h"
#include "app/capp.h"
#include "core/cobject.h"
#include "sprite2d/csprite2d.h"

int i =(180+2)%360;
int j =(30+2)%360;
int fps;
CObject3D* sprite;
void _onEnterFrame(CObject*  obj, CObject* cgame) {
  i =(i+10)%360;

  csprite2d_setRXYZ((CSprite2D*)sprite, 0.0, 0.0, 2*3.14*i/360.0);
  csprite2d_update((CSprite2D*)sprite);

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
  sprite = (CObject3D*)createCSprite2D(50, 50);
  CDynaTexAtlas* atlas = cgame_getCDynaTexAtlas(gameObj, 0);
  CImage* img = ctexAtlas_getImage(atlas);
  CDynaBlockSpace out;
  ctexAtlas_addImageFromPath(atlas, "examples/assets/icon.png", &out);

  csprite2d_setImage((CSprite2D*)sprite, img, &out);

  //
  CObject3D* root = cgame_getRoot(gameObj);
  cobject3d_addNode(root, (CObject3D*)sprite);
  ccamera3d_updateAtPerspective(cgame_getCamera(gameObj),
      0.0, 0.0, 5.0,
      0.0, 0.0, 0.0,
      3.14*45.0/180.0, 400.0/300.0, 0.5, 1000.0);

  cgame_run(gameObj);

  return 0;
}
