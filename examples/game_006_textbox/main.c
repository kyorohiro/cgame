#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "game/ccamera3d.h"
#include "matrix/cmatrix.h"
#include "app/capp.h"
#include "core/cobject.h"
#include "sprite2d/csprite2d.h"
#include <string.h>

int i =(180+2)%360;
int j =(30+2)%360;
int fps;
CObject3D* sprite001;
CTtf* ttf;
CDynaBlockSpace out1;
double startTime;
int z = 0;
char src[]= " Hello, World!! Test Test Test Test";
int w,h;

void _onEnterFrame(CObject*  obj, CObject* cgame) {
  i =(i+10)%360;
  double currentTime =  capp_currentMilliSecound(getCApp());
  int intervalTime = (int)((currentTime - startTime)/1000*9.0);
  CDynaTexAtlas* atlas = cgame_getCDynaTexAtlas(getCGame(), 0);
  if(intervalTime <30) {
    if(z != intervalTime) {
      printf("%d %d\r\n", intervalTime, (int)sizeof(src));
      z = intervalTime;
      ctexAtlas_clear(atlas);

      char t[64];
      strncpy( t, (char*)src, intervalTime );
      ctexAtlas_addImageFromCTtf(atlas, ttf, t, 1.0, 1.0, 1.0, 1.0, &out1);
      out1.w = w;
      out1.h = h;
      csprite2d_setImage((CSprite2D*)sprite001, ctexAtlas_getImage(atlas), &out1);
      csprite2d_update((CSprite2D*)sprite001);
    }
  } else {
    //ctexAtlas_clear(atlas);
  }



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
  startTime =  capp_currentMilliSecound(getCApp());
  //
  CDynaTexAtlas* atlas = cgame_getCDynaTexAtlas(gameObj, 0);
  ttf = cttfMgr_createTtf(getCTtfMgr(), "examples/assets/Roboto-Bold.ttf", 60);
  int ret = ctexAtlas_addImageFromCTtf(atlas, ttf, src, 1.0, 1.0, 1.0, 1.0, &out1);
  cttf_sizeText(ttf, src, &w,&h);
  sprite001 = (CObject3D*)createCSprite2D(2.0, 2.0*h/w);
  csprite2d_setImage((CSprite2D*)sprite001, ctexAtlas_getImage(atlas), &out1);
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
