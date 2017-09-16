#ifndef _H_3DPRIMITIVE
#define _H_3DPRIMITIVE


#include "core/cobject.h"
#include "core/cmemory.h"
#include "matrix/cmatrix4.h"
#include "core/cbytes.h"
#include "core/clinkedList.h"
#include "matrix/cmatrix4.h"
#include "app/cimage.h"

#define PRIMITIVE3D_NAME "pr3"
#define PRIMITIVE3D_BUFFER_SIZE 10

typedef struct {
  CObject3D parent;
  CBytes *vertexes;
  CBytes *normals;
  CBytes *colors;
  CBytes *indexes;
  CImage *image;
  CBytes *texCoords;
} CPrimitive3D;



CPrimitive3D* newCPrimitive3D(CMemory* mem);
CPrimitive3D* initCPrimitive3D(CPrimitive3D*);
CPrimitive3D* initCPrimitive3DAsCube(CPrimitive3D*);
CPrimitive3D* initCPrimitive3DAsTriangle(CPrimitive3D* obj);
CPrimitive3D* initCPrimitive3DAsSquare(CPrimitive3D* obj);

CPrimitive3D* createCPrimitive3DAsCube();
CPrimitive3D* createCPrimitive3DAsTriangle();
CPrimitive3D* createPrimitive3DAsSquare();
CPrimitive3D* createCPrimitive3DAsTinyShape(CMatrixVertexType* src, int length);


// src  x,y,x,y,x,y......
CPrimitive3D* initCPrimitive3DAsTinyShape(CPrimitive3D* obj, CMatrixVertexType* src, int length);
void freeCPrimitive3D(void* obj);
CPrimitive3D* cprimitive3d_setColor(CPrimitive3D*, double r, double g, double b, double a);


//
//
char* cprimitive3d_getIndexBinary(CPrimitive3D*);
int cprimitive3d_getIndexBinaryLength(CPrimitive3D*);

char* cprimitive3d_getVertexBinary(CPrimitive3D*);
int cprimitive3d_getVertexBinaryLength(CPrimitive3D*);

char* cprimitive3d_getNormalBinary(CPrimitive3D*);
int cprimitive3d_getNormalBinaryLength(CPrimitive3D*);

char* cprimitive3d_getColorBinary(CPrimitive3D*);
int cprimitive3d_getColorBinaryLength(CPrimitive3D*);

//
void cprimitive3d_setCImage(CPrimitive3D* obj, CImage* img);
CImage* cprimitive3d_getCImage(CPrimitive3D* obj);
char* cprimitive3d_getTextCoordBinary(CPrimitive3D*);
int cprimitive3d_getTextCoordLength(CPrimitive3D*);

//
CPrimitive3D* cprimitive3d_setTexCoordAsSquare(CPrimitive3D* obj, CMatrixVertexType x0, CMatrixVertexType y0, CMatrixVertexType x1, CMatrixVertexType y1, CMatrixVertexType x2, CMatrixVertexType y2, CMatrixVertexType x3, CMatrixVertexType y3);
CPrimitive3D* cprimitive3d_setTexCoordAsSquareFromBlock(CPrimitive3D* obj, int x, int y, int w, int h, int imgW, int imgH);
CPrimitive3D* cprimitive3d_setTexCoordAsTinyShapeFromBlock(CPrimitive3D* obj, int x, int y, int w, int h, int imgW, int imgH);
void cprimitive3d_show(CPrimitive3D* obj);
#endif
