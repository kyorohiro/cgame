#include "csprite2d.h"
#include <stdio.h>

void freeCSprite2D(void* obj) {
  CSprite2D* objTmp = obj;
  freeCObject3D(obj);
}

CSprite2D* newCSprite2D(CMemory* mem) {
  CSprite2D* ret = cmemory_calloc(mem, 1, sizeof(CSprite2D));
  ((CObject*)ret)->cmemory = mem;
  ((CObject*)ret)->funcFree = freeCSprite2D;
  return ret;
}

CSprite2D* initCSprite2D(CSprite2D* obj, CMatrixVertexType w, CMatrixVertexType h) {
  CMemory* mem = cobject_getCMemory((CObject*)obj);
  CMatrixVertexType src[] = {
//    -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, -1.0,  // A 0-3
   -1.0*w, 1.0*h, 1.0*w, 1.0*h, 1.0*w, -1.0*h, -1.0*w, -1.0*h,  // A 0-3
  };
  initCPrimitive3DAsTinyShape((CPrimitive3D*)obj, src, 8);
  obj->texMat = cmatrix4_setIdentity(initCMatrix4(newCMatrix4(mem)));
  return obj;
}

CSprite2D* createCSprite2D(CMatrixVertexType width, CMatrixVertexType height) {
  return initCSprite2D(newCSprite2D(getCMemory()), width, height);
}

CSprite2D* csprite2d_setXYZ(CSprite2D* obj, CMatrixVertexType x, CMatrixVertexType y, CMatrixVertexType z) {
  obj->x = x;
  obj->y = y;
  obj->z = z;
  return obj;
}

CSprite2D* csprite2d_setRXYZ(CSprite2D* obj, CMatrixVertexType rx, CMatrixVertexType ry, CMatrixVertexType rz) {
  obj->rx = rx;
  obj->ry = ry;
  obj->rz = rz;
  return obj;
}

CSprite2D* csprite2d_update(CSprite2D* obj) {
  CObject3D* obj3d = (CObject3D*)obj;
  cmatrix4_setXyxRXyzSXyz(cobject3d_getCMatrix4(obj3d),
                obj3d->centerX, obj3d->centerY, obj3d->centerZ,
                obj->x, obj->y, obj->z,
                obj->rx, obj->ry, obj->rz,
                1.0, 1.0, 1.0);
  return obj;
}

CSprite2D* csprite2d_setImage(CSprite2D* obj, CImage* img, CDynaBlockSpace* block) {
  CMatrixValueType x,y,w,h;
  CMatrixValueType iw = cimage_getWidth(img);
  CMatrixValueType ih = cimage_getHeight(img);
  if(block == NULL) {
    x = 0;
    y = 0;
    w = iw;
    h = ih;
  } else {
    x = block->x;
    y = block->y;
    w = block->w;
    h = block->h;
  }

  obj->texX = 0.0;
  obj->texY = 0.0;
  obj->texZ = 0.0;
  obj->texRx = 0.0;
  obj->texRy = 0.0;
  obj->texRz = 0.0;
  obj->texCx = (x + w/2.0)/iw;
  obj->texCy = (y + h/2.0)/ih;
  obj->texCz = 0.0;

  obj->texBlockX = x;
  obj->texBlockY = y;
  obj->texBlockW = w;
  obj->texBlockH = h;
  obj->imageW = iw;
  obj->imageH = ih;

  cprimitive3d_setCImage((CPrimitive3D*)obj, img);
  cprimitive3d_setTexCoordAsTinyShapeFromBlock((CPrimitive3D*)obj, x, y, w, h, iw, ih);
    return obj;
}

CSprite2D* csprite2d_setTexXYZ(CSprite2D* obj, CMatrixVertexType x, CMatrixVertexType y, CMatrixVertexType z) {
  obj->texX = x;
  obj->texY = y;
  obj->texZ = z;
  return obj;
}

CSprite2D* csprite2d_setTexRXYZ(CSprite2D* obj, CMatrixVertexType rx, CMatrixVertexType ry, CMatrixVertexType rz) {
  obj->texRx = rx;
  obj->texRy = ry;
  obj->texRz = rz;
  return obj;
}

CSprite2D* csprite2d_updateTex(CSprite2D* obj) {
  CObject3D* obj3d = (CObject3D*)obj;
  cmatrix4_setXyxRXyzSXyz(obj->texMat,
                -obj->texCx, -obj->texCy, -obj->texCz,
                obj->texX, obj->texY, obj->texZ,
                obj->texRx, obj->texRy, obj->texRz,
                1.0, 1.0, 1.0);

//  printf("center = %f %f %f\r\n",obj->texCx, obj->texCy, obj->texCz);
  cprimitive3d_setTexCoordAsTinyShapeFromBlockWithTrans((CPrimitive3D*)obj,
      obj->texMat,
      obj->texBlockX, obj->texBlockY, obj->texBlockW, obj->texBlockH,
      obj->imageW, obj->imageH);
  return obj;
}
