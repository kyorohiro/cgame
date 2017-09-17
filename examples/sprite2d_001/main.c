#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "game/ccamera3d.h"
#include "matrix/cmatrix.h"
#include "app/capp.h"
#include "core/cobject.h"


int i =(180+2)%360;
int j =(30+2)%360;
int fps;
void _onEnterFrame(CObject*  obj, CObject* cgame) {

  CApp* appObj = getCApp();
  CGame* gameObj = getCGame();

  if(fps != appObj->fps) {
    fps = appObj->fps;
    printf("fps:%d;\r\n",fps);
  }

  cgame_postRedisplay(gameObj);

}


int main(int argc, char** argv) {
  printf("call main\r\n");
  CGame* gameObj = createCGame(400, 300);

  CObject3D *root = cgame_getRoot(gameObj);
  cobject3d_addNode(root, (CObject3D*)createCPrimitive3DAsTriangle());
  CObject3D *cube = cobject3d_setOnEnterFrameFunc((CObject3D*)createCPrimitive3DAsCube(), _onEnterFrame);
  cobject3d_addNode(root, cube);

  ccamera3d_updateAtPerspective(cgame_getCamera(gameObj),
      0.0, 0.0, 5.0,
      0.0, 0.0, 0.0,
      3.14*45.0/180.0, 400.0/300.0, 0.5, 1000.0);

  cgame_run(gameObj);

  return 0;
}
