#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "game/ccamera3d.h"
#include "matrix/cvector4.h"
#include "matrix/cglmatrix.h"
#include "app/capp.h"
#include "core/cobject.h"
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

  cmatrix4_setRotationX(initCMatrix4(&rotXMat), 3.14*i/180.0);
  cmatrix4_setRotationY(initCMatrix4(&rotYMat), 3.14*i/180.0);
  cmatrix4_setRotationZ(initCMatrix4(&rotZMat), 3.14*i/180.0);

  CMatrix4 *mat = cobject3d_getCMatrix4((CObject3D*)obj);

  cmatrix4_setTranslation(initCMatrix4(mat), 0.0, 0.0, -2.0);

  cmatrix4_multiply(&rotYMat, mat, mat);
//  cmatrix4_multiply(mat, &rotXMat, mat);
//  cmatrix4_multiply(mat, &rotYMat, mat);
//  cmatrix4_multiply(mat, &rotZMat, mat);

  //
  CAppMouseEvent *event = cgame_getCurrentMouseEvent(gameObj);
  //printf(">> %f %f \r\n", event->x, event->y);



  CApp *app = getCApp();

  double mouseX = event->x;//400;
  double mouseY = event->y;//300;
  CCamera3D* camera = cgame_getCamera(gameObj);
  CVector4* vec1 = cglmatrix4_unProject(
    mouseX, 300-mouseY, 1.0,
    camera->view,
    camera->projection,
    0.0, 0.0, 400.0, 300.0);

  CVector4* vec2 = cglmatrix4_unProject(
    mouseX, 300-mouseY, 100.0,
    camera->view, camera->projection,
    0.0, 0.0, 400.0, 1000.0);
  cprimitive3d_setColor((CPrimitive3D*)obj, 1.0,0.0,0.0,1.0);

  if(event->state == 1) {
    printf(">Aa>%f %f : %f %f %f %f\r\n",event->x,event->y,vec1->value[0],vec1->value[1],vec1->value[2],vec1->value[3]);
//    printf(">Ab>%f %f : %f %f %f %f\r\n",event->x,event->y,vec1m->value[0],vec1m->value[1],vec1m->value[2],vec1m->value[3]);
    printf(">B>%f %f : %f %f %f %f\r\n",event->x,event->y,vec2->value[0],vec2->value[1],vec2->value[2],vec2->value[3]);
//    printf(">B>%f %f : %f %f %f %f\r\n",event->x,event->y,vec2m->value[0],vec2m->value[1],vec2m->value[2],vec2m->value[3]);

  }
  releaseCObject((CObject*)vec1);
  releaseCObject((CObject*)vec2);
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

/*
  ccamera3d_update(cgame_getCamera(gameObj),
    0.0, 3.0, 5.3,
    3.14*-45/180.0, 0.0, 0.0,
    3.14*90.0/180.0, 1.0, 0.5, 1000.0);
*/

  ccamera3d_update(cgame_getCamera(gameObj),
      0.0, 0.0, 5.0,
      0.0, 0.0, 0.0,
      3.14*45.0/180.0, 400.0/300.0, 0.5, 1000.0);

  cgame_start(gameObj);

  return 0;
}
