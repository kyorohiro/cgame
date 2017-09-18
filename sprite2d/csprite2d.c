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
  CMatrix4Raw center;
  CMatrix4Raw centerB;
  CMatrix4Raw move;

  CMatrix4Raw rotateX;
  CMatrix4Raw rotateY;
  CMatrix4Raw rotateZ;
  cmatrix4raw_setTranslation(center, obj3d->centerX, obj3d->centerY, obj3d->centerZ);
  cmatrix4raw_setRotationX(rotateX, obj->rx);
  cmatrix4raw_setRotationY(rotateY, obj->ry);
  cmatrix4raw_setRotationZ(rotateZ, obj->rz);
  cmatrix4raw_setTranslation(centerB, obj3d->centerX, obj3d->centerY, obj3d->centerZ);
  cmatrix4raw_setTranslation(move, obj->x, obj->y, obj->z);

  CMatrix4* mat = obj3d->mat;
  cmatrix4_setIdentity(mat);
  cmatrix4raw_mul(center, mat->value, mat->value);
  cmatrix4raw_mul(rotateX, mat->value, mat->value);
  cmatrix4raw_mul(rotateY, mat->value, mat->value);
  cmatrix4raw_mul(rotateZ, mat->value, mat->value);

  cmatrix4raw_mul(centerB, mat->value, mat->value);
  cmatrix4raw_mul(move, mat->value, mat->value);

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
