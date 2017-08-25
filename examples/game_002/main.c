#include <stdio.h>
#include "game/cgame.h"
#include "game/cobject3d.h"
#include "game/cprimitive3d.h"
#include "game/ccamera3d.h"
#include "matrix/cmatrix.h"
#include "matrix/cmatrix4.h"
#include "matrix/cmatrix_proj.h"


//#include "matrix/cray.h"
#include "app/capp.h"
#include "core/cobject.h"

void _onEnterFrame(CObject*  obj, CObject* cgame) {
  CGame* gameObj = getCGame();
  CObject3D* obj3D = (CObject3D*)obj;
  CMatrix4 *mat = cobject3d_getCMatrix4(obj3D);
  cmatrix4_setTranslation(initCMatrix4(mat), 0.5, 1.0, -2.0);
  CAppMouseEvent *event = cgame_getCurrentMouseEvent(gameObj);

  CVector4Raw dv1;
  CVector4Raw dv2;
  CVector4Raw dv3;
  cvector4raw_setValues(dv1,-0.5, 0.5, 0.0, 0.0);
  cvector4raw_setValues(dv2, 0.5, 0.5, 0.0, 0.0);
  cvector4raw_setValues(dv3,-0.5,-0.5, 0.0, 0.0);
  cmatrix4raw_mulVector4Raw(mat->value, dv1, dv1);
  cmatrix4raw_mulVector4Raw(mat->value, dv2, dv2);
  cmatrix4raw_mulVector4Raw(mat->value, dv3, dv3);



  double mouseX = event->x -200;
  double mouseY = event->y -150;//300;
  CCamera3D* camera = cgame_getCamera(gameObj);

  if(event->state == 1) {
    //
    //
    CMatrix4Raw tmp;
//    CVector3Raw out1;
    CVector3Raw out2;
    cmatrix4raw_mul(camera->projection->value, camera->view->value, tmp);
  //  cmatrix4raw_unproject(tmp, -mouseX, 400.0, mouseY, 300.0, 200.0, 150.0, 0.0, out1);
    cmatrix4raw_unproject(tmp, -mouseX, 400.0, mouseY, 300.0, 200.0, 150.0, 1.0, out2);
    printf("# %f %f\r\n", mouseX, mouseY);
    //cvector3raw_show(out1);
    cvector3raw_show(out2);


    //
    //
    //
    CVector3Raw ori;
    CVector3Raw dir;
    cvector3raw_setValues(ori, 0.0, 0.0, 5.0);
    cvector3raw_sub(out2, ori, dir);
    //
    //
    CVector4Raw p0;
    CVector4Raw p1;
    CVector4Raw p2;
    cvector3raw_setValues(p0,0.0f, 0.5f, 0.0f);
    cvector3raw_setValues(p1,-0.5f, -0.5f, 0.0f);
    cvector3raw_setValues(p2,0.5f, -0.5f, 0.0f);
    cmatrix4raw_mulVector(obj3D->mat->value, p0[0], p0[1], p0[2], 1.0, p0);
    cmatrix4raw_mulVector(obj3D->mat->value, p1[0], p1[1], p1[2], 1.0, p1);
    cmatrix4raw_mulVector(obj3D->mat->value, p2[0], p2[1], p2[2], 1.0, p2);
    //
    CMatrixVertexType rock = crayraw_intersectsWithTriangle(ori, dir,
      p0, p1, p2);

    printf(" rock = %f \r\n", rock);

    printf("\r\n");
  }
//  cmatrix4_unproject();
/*
  CVector4* vec1 = cglmatrix4_unProject(
    mouseX, 300-mouseY, 0.5,
    camera->view,
    camera->projection,
    0.0, 0.0, 400.0, 300.0);*/
/*

  double mouseX = event->x;//400;
  double mouseY = event->y;//300;
  CCamera3D* camera = cgame_getCamera(gameObj);
  CVector4* vec1 = cglmatrix4_unProject(
    mouseX, 300-mouseY, 0.5,
    camera->view,
    camera->projection,
    0.0, 0.0, 400.0, 300.0);

  CVector4* vec2 = cglmatrix4_unProject(
    mouseX, 300-mouseY, 10.0,
    camera->view, camera->projection,
    0.0, 0.0, 400.0, 300.0);
  cprimitive3d_setColor((CPrimitive3D*)obj, 1.0,0.0,0.0,1.0);

  // ray
  //CRay* ray  = initCRay(newCRay(getCMemory()),
  //  0.25,0.25,2.0,
  //  0.0,0.0, -1.0
//  vec1->value[0],vec1->value[1],vec1->value[2],
//  vec2->value[0]-vec1->value[0],vec2->value[1]-vec1->value[1], 1.0*(vec2->value[2]-vec1->value[2])
  //);
  //
  //CVector3Raw v1; v1[0] = dv1.value[0];v1[1] = dv1.value[1];v1[2] = dv1.value[2];
  //CVector3Raw v2; v2[0] = dv2.value[0];v2[1] = dv2.value[1];v2[2] = dv2.value[2];
  //CVector3Raw v3; v3[0] = dv3.value[0];v3[1] = dv3.value[1];v3[2] = dv3.value[2];
//  double d = crayraw_intersectsWithTriangle2(ray, v1, v2, v3);
  //double d = crayraw_intersectsWithTriangle(ray, v1, v2, v3);
  //*/
//  if(event->state == 1) {
//    printf(">Aa>%f %f : %f %f %f %f\r\n",event->x,event->y,vec1->value[0],vec1->value[1],vec1->value[2],vec1->value[3]);
//    printf(">Ab>%f %f : %f %f %f %f\r\n",event->x,event->y,vec1m->value[0],vec1m->value[1],vec1m->value[2],vec1m->value[3]);
//    printf(">B>%f %f : %f %f %f %f\r\n",event->x,event->y,vec2->value[0],vec2->value[1],vec2->value[2],vec2->value[3]);
//    printf(">B>%f %f : %f %f %f %f\r\n",event->x,event->y,vec2m->value[0],vec2m->value[1],vec2m->value[2],vec2m->value[3]);

    //printf(">N>%f\r\n", d);
    //cvector3raw_show(v1);
    //cvector3raw_show(v2);
    //cvector3raw_show(v3);
    //cray_show(ray);
    //
/*
  releaseCObject((CObject*)vec1);
  releaseCObject((CObject*)vec2);
  //releaseCObject((CObject*)ray);
*/
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
  CObject3D *cube1 = (CObject3D*)initCPrimitive3DAsTriangle(newCPrimitive3D(getCMemory()));

  cube1->onEnterFrameFunc =_onEnterFrame;
  cobject3d_addNode(root, cube1);

/*
  ccamera3d_update(cgame_getCamera(gameObj),
    0.0, 3.0, 5.3,
    3.14*-45/180.0, 0.0, 0.0,
    3.14*90.0/180.0, 1.0, 0.5, 1000.0);
*/

  ccamera3d_update(cgame_getCamera(gameObj),
      0.0, 0.0, 5.0,
      0.0, 0.0, 0.0,
      3.14*45.0*0.5/180.0, 400.0/300.0, 0.5, 100.0);

  cgame_start(gameObj);

  return 0;
}
