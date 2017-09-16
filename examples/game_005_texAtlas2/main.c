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
#include "app/cttf.h"
#include "core/cobject.h"
#include <math.h>

int main(int argc, char** argv) {
  printf("call main 1\r\n");
  CGame* gameObj = createCGame(400, 300);
  CImageMgr* mgr = getCImageMgr();
  //
  printf("call main 2\r\n");
  CDynaTexAtlas* atlas = cgame_getCDynaTexAtlas(gameObj, 0);
  CDynaBlockSpace out1;
  CDynaBlockSpace out2;

  //
  // create image
  //
  CTtf* font = cttfMgr_createTtf(getCTtfMgr(), "./examples/assets/Roboto-Bold.ttf", 60);
  int ret = ctexAtlas_addImageFromCTtf(atlas, font, "test", 1.0, 1.0, 1.0, 1.0, &out1);
  ctexAtlas_addImageFromPath(atlas, "examples/assets/icon.png", &out2);


  //
  // create shape
  //
  int vertexNum = 6;
  CMatrixVertexType shapeSrc[vertexNum*2];
  for(int i=0;i<vertexNum;i++) {
      shapeSrc[2*i + 0] = 0.45*cos(M_PI/180*(360.0/vertexNum)*-i+0);
      shapeSrc[2*i + 1] = 0.45*sin(M_PI/180*(360.0/vertexNum)*-i+0);
  }
  CObject3D *square1 = (CObject3D*)createCPrimitive3DAsTinyShape(shapeSrc, vertexNum*2);
  CObject3D *square2 = (CObject3D*)createCPrimitive3DAsTinyShape(shapeSrc, vertexNum*2);

  //
  // set parameter 1
  //
  cmatrix4_setTranslation(cobject3d_getCMatrix4((CObject3D*)square1), 0.0, 0.0, 0.0);
  cprimitive3d_setCImage((CPrimitive3D*)square1, ctexAtlas_getImage(atlas));
  cprimitive3d_setColor((CPrimitive3D*)square1, 0.5,0.5,1.0,1.0);
  cmatrix4_setTranslation(cobject3d_getCMatrix4((CObject3D*)square1), -0.5, 0.5, -1.5);

  cprimitive3d_setTexCoordAsTinyShapeFromBlock((CPrimitive3D*)square1, out1.x, out1.y, out1.w, out1.h,
    ctexAtlas_getWidth(atlas), ctexAtlas_getHeight(atlas));


  //
  // set parameter 2
  //
  cmatrix4_setTranslation(cobject3d_getCMatrix4((CObject3D*)square2), 0.0, 0.0, 0.0);
  cprimitive3d_setCImage((CPrimitive3D*)square2, ctexAtlas_getImage(atlas));
  cprimitive3d_setColor((CPrimitive3D*)square2, 0.5,0.5,1.0,1.0);
  cmatrix4_setTranslation(cobject3d_getCMatrix4((CObject3D*)square2), 0.5, -0.5, -1.5);
  cprimitive3d_setTexCoordAsTinyShapeFromBlock((CPrimitive3D*)square2, out2.x, out2.y, out2.w, out2.h,
    ctexAtlas_getWidth(atlas), ctexAtlas_getHeight(atlas));


  //
  // add node in tree
  //
  cprimitive3d_show((CPrimitive3D*)square1);
  CObject3D *root = cgame_getRoot(gameObj);
  cobject3d_addNode(root, square1);
  cobject3d_addNode(root, square2);


  //
  // setup camera
  //
  ccamera3d_update(cgame_getCamera(gameObj),
      0.0, 0.0, 5.0,
      0.0, 0.0, 0.0,
      3.14*45.0*0.5/180.0, 400.0/300.0, 0.5, 100.0);

  
  cgame_run(gameObj);
  return 0;
}
