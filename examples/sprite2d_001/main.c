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
void _onEnterFrame(CObject*  obj, CObject* cgame) {
  i =(180+2+i)%360;
  CApp* appObj = getCApp();
  CGame* gameObj = getCGame();
  CSprite2D* sprite = (CSprite2D*)obj;
  csprite2d_setRXYZ(sprite, 0.0, 0.0, 3.14*i/360.0);
  csprite2d_update(sprite);

  if(fps != appObj->fps) {
    fps = appObj->fps;
    printf("fps:%d;\r\n",fps);
  }

  cgame_postRedisplay(gameObj);
}


int main(int argc, char** argv) {
  printf("call main\r\n");
  CGame* gameObj = createCGame(400, 300);
  CObject3D* root = cgame_getRoot(gameObj);
  CObject3D* sprite = (CObject3D*)createCSprite2D(50, 50);
  cobject3d_setOnEnterFrameFunc((CObject3D*)sprite, _onEnterFrame);
  cobject3d_addNode(root, (CObject3D*)sprite);

  ccamera3d_updateAtPerspective(cgame_getCamera(gameObj),
      0.0, 0.0, 5.0,
      0.0, 0.0, 0.0,
      3.14*45.0/180.0, 400.0/300.0, 0.5, 1000.0);

  cgame_run(gameObj);

  return 0;
}
