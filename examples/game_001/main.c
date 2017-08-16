#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "game/ccamera3d.h"
#include "matrix/cvector4.h"
#include "app/capp.h"
int i =(20+2)%360;
int j=0;
void _onEnterFrame(CObject*  obj, CObject* cgame) {
//  CGame* gameObj = (CGame*)cgame;
  CGame* gameObj = getCGame();
  i = (i+2)%360;
  j++;
  CMatrix4 rotYMat;
  CMatrix4 rotZMat;
  CMatrix4 rotXMat;

  cmatrix4_setRotationY(&rotYMat, 3.14*i/180.0);
  cmatrix4_setRotationZ(&rotZMat, 3.14*i/180.0);
//  cmatrix4_setRotationZ(&rotZMat, 3.14*i/180.0);
  cmatrix4_setRotationX(&rotXMat, 3.14*i/180.0);

  CMatrix4 *mat = cobject3d_getCMatrix4((CObject3D*)obj);

  cmatrix4_setTranslation(initCMatrix4(mat), 0.0, 0.0, -2.0);

  cmatrix4_multiply(&rotYMat, mat, mat);
  cmatrix4_multiply(mat, &rotXMat, mat);
  cmatrix4_multiply(mat, &rotYMat, mat);
  cmatrix4_multiply(mat, &rotZMat, mat);

  //
  CAppMouseEvent *event = cgame_getCurrentMouseEvent(gameObj);
  //printf(">> %f %f \r\n", event->x, event->y);



  CApp *app = getCApp();
  double x = (event->x-(app->width/2.0))/(app->width/2.0);
  double y = -1*(event->y-(app->height/2.0))/(app->height/2.0);

  CVector4* out = cgame_getLocalPointFromGlobal(gameObj, 0.0, 3.0, 0.5, mat, NULL);
  CVector4* out2 = cgame_getLocalPointFromGlobal(gameObj, 0.0, 3.0,100.3, mat, NULL);
  cprimitive3d_setColor((CPrimitive3D*)obj, 1.0,0.0,0.0,1.0);
  if(-0.5<out->value[0] && out->value[0]< 0.5) {
    if(-0.5<out->value[1] && out->value[1]< 0.5) {
      cprimitive3d_setColor((CPrimitive3D*)obj, 1.0,1.0,0.0,0.0);
    }
  }
  if(event->state == 1) {
    printf(">A>%f %f :: %f %f %f %f\r\n",x, y, out->value[0],out->value[1],out->value[2],out->value[3]);
    printf(">B>%f %f :: %f %f %f %f\r\n",x, y, out2->value[0],out2->value[1],out2->value[2],out2->value[3]);
  }

  //
  // post redisplay
  //if(j < 200)
  {
    cgame_postRedisplay(gameObj);
  }

}

int main(int argc, char** argv) {
  printf("test");

  CGame* gameObj = getCGame();
  CObject3D *root = cgame_getRoot(gameObj);
  CObject3D *cube1 = (CObject3D*)initCPrimitive3DAsCube(newCPrimitive3D(getCMemory()));
  CObject3D *cube2 = (CObject3D*)initCPrimitive3DAsTriangle(newCPrimitive3D(getCMemory()));

  cube1->onEnterFrameFunc =_onEnterFrame;
  cobject3d_addNode(root, cube1);
  cobject3d_addNode(root, cube2);

  ccamera3d_update(cgame_getCamera(gameObj),
    0.0, 3.0, 5.3,
    3.14*-45/180.0, 0.0, 0.0,
    3.14*90.0/180.0, 1.0, 0.5, 1000.0);
/*
  ccamera3d_update(cgame_getCamera(gameObj),
      0.0, 0.0, 5.3,
      0.0, 0.0, 0.0,
      3.14*90.0/180.0, 1.0, 0.5, 1000.0);
*/
  cgame_start(gameObj);

  return 0;
}
