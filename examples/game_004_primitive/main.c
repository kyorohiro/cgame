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
  //
  CObject3D *square = (CObject3D*)createCPrimitive3DAsTriangle();
  int vertexNum = 12;
  CMatrixVertexType shapeSrc[vertexNum*2];
  for(int i=0;i<vertexNum;i++) {
      shapeSrc[2*i + 0] = 0.5*cos(M_PI/180*(360.0/vertexNum)*-i);
      shapeSrc[2*i + 1] = 0.5*sin(M_PI/180*(360.0/vertexNum)*-i);
  }
  CObject3D* shape = (CObject3D*)createCPrimitive3DAsTinyShape(shapeSrc, vertexNum*2);

  printf("#square\r\n");
  cprimitive3d_show((CPrimitive3D*)square);
  printf("#shape\r\n");
  cprimitive3d_show((CPrimitive3D*)shape);

  cmatrix4_setTranslation(cobject3d_getCMatrix4(square), 0.5, 0.5, 0.0);
  cmatrix4_setTranslation(cobject3d_getCMatrix4(shape), 0.0, 0.0, 0.0);
  //
  //
  CObject3D *root = cgame_getRoot(gameObj);
  cobject3d_addNode(root, square);
  cobject3d_addNode(root, shape);

  ccamera3d_update(cgame_getCamera(gameObj),
      0.0, 0.0, 5.0,
      0.0, 0.0, 0.0,
      3.14*45.0*0.5/180.0, 400.0/300.0, 0.5, 100.0);

  cgame_run(gameObj);
  return 0;
}
