
#ifndef __H_CMatrix4
#define __H_CMatrix4


#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvectorMath_inner.h"
#include "cvector4.h"


typedef CVMFloat CMatrix4Raw[16];
typedef CVMFloat *CMatrix4RawRef;

typedef struct {
  CObject parent;
  CMatrix4Raw value;
} CMatrix4;

CMatrix4* newCMatrix4(CMemory*);
CMatrix4* initCMatrix4(CMatrix4*);
CMatrix4* createCMatrix4();
CMatrix4* cmatrix4_setIdentity(CMatrix4* obj);
CMatrix4* cmatrix4_setValues(CMatrix4* obj,
              CVMFloat a11, CVMFloat a12, CVMFloat a13, CVMFloat a14,
              CVMFloat a21, CVMFloat a22, CVMFloat a23, CVMFloat a24,
              CVMFloat a31, CVMFloat a32, CVMFloat a33, CVMFloat a34,
              CVMFloat a41, CVMFloat a42, CVMFloat a43, CVMFloat a44);

CMatrix4* cmatrix4_add(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_sub(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CMatrix4* cmatrix4_mul(CMatrix4* obj, CMatrix4* arg, CMatrix4* out);
CVector4* cmatrix4_mulCVector4(CMatrix4* obj, CVector4* arg, CVector4* out);
CMatrix4* cmatrix4_transpose(CMatrix4* obj, CMatrix4* out);
CVMFloat cmatrix4_determinant(CMatrix4* obj);
CMatrix4* cmatrix4_inverse(CMatrix4* obj, CMatrix4* outInverse, CVMFloat *outDeterminant);

//     col 0 1 2 3
// row
//   0
//   1
//   2
//   3
CVMFloat cmatrix4_getValue(CMatrix4* obj, int row, int col);
void cmatrix4_show(CMatrix4* obj);


//
//
// RAW
//
//
CMatrix4RawRef cmatrix4raw_setIdentity(CMatrix4RawRef obj);

CMatrix4RawRef cmatrix4raw_setValues(CMatrix4RawRef obj,
              CVMFloat a11, CVMFloat a12, CVMFloat a13, CVMFloat a14,
              CVMFloat a21, CVMFloat a22, CVMFloat a23, CVMFloat a24,
              CVMFloat a31, CVMFloat a32, CVMFloat a33, CVMFloat a34,
              CVMFloat a41, CVMFloat a42, CVMFloat a43, CVMFloat a44
            );
CMatrix4RawRef cmatrix4raw_copy(CMatrix4RawRef obj, CMatrix4RawRef out);
CMatrix4RawRef cmatrix4raw_add(CMatrix4RawRef obj, CMatrix4RawRef arg, CMatrix4RawRef out);
CMatrix4RawRef cmatrix4raw_sub(CMatrix4RawRef obj, CMatrix4RawRef arg, CMatrix4RawRef out);
CMatrix4RawRef cmatrix4raw_mul(CMatrix4RawRef obj, CMatrix4RawRef arg, CMatrix4RawRef out);
CVector4RawRef cmatrix4raw_mulVector4Raw(CMatrix4RawRef obj, CVector4RawRef arg, CVector4RawRef out);
CVector4RawRef cmatrix4raw_mulVector(CMatrix4RawRef obj, CVMFloat x,  CVMFloat y, CVMFloat z, CVMFloat w, CVector4RawRef out);

CMatrix4RawRef cmatrix4raw_transpose(CMatrix4RawRef obj, CMatrix4RawRef out);
CVMFloat cmatrix4raw_determinant(CMatrix4RawRef obj);
CMatrix4RawRef cmatrix4raw_inverse(CMatrix4RawRef obj, CMatrix4RawRef outInverse, CVMFloat *outDeterminant);


CVMFloat cmatrix4raw_getValue(CMatrix4RawRef obj, int row, int col);
void cmatrix4raw_show(CMatrix4RawRef obj);

#endif
