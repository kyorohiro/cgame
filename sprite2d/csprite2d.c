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

CSprite2D* initCSprite2D(CSprite2D* obj, int width, int height) {
  initCPrimitive3DAsSquare((CPrimitive3D*)obj);
  return obj;
}

CSprite2D* createCSprite2D(int width, int height) {
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
