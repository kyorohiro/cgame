#ifndef __H_CMatrix2
#define __H_CMatrix2

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvector2.h"
#include "cvectorMath_inner.h"



typedef CVMFloat CMatrix2Raw[4];
typedef CVMFloat *CMatrix2RawRef;

typedef struct {
  CObject parent;
  CMatrix2Raw value;
} CMatrix2;

CMatrix2* newCMatrix2(CMemory*);
CMatrix2* initCMatrix2(CMatrix2*);
CMatrix2* createCMatrix2();

CMatrix2* cmatrix2_setIdentity(CMatrix2* obj);
CMatrix2* cmatrix2_setValues(CMatrix2* obj,
              CVMFloat a11, CVMFloat a12,
              CVMFloat a21, CVMFloat a22);

CMatrix2* cmatrix2_add(CMatrix2* obj, CMatrix2* arg, CMatrix2* out);
CMatrix2* cmatrix2_sub(CMatrix2* obj, CMatrix2* arg, CMatrix2* out);
CMatrix2* cmatrix2_mul(CMatrix2* obj, CMatrix2* arg, CMatrix2* out);
CVector2* cmatrix2_mulCVector2(CMatrix2* obj, CVector2* arg, CVector2* out);
CMatrix2* cmatrix2_transpose(CMatrix2* obj, CMatrix2* out);
CVMFloat cmatrix2_determinant(CMatrix2* obj);
CMatrix2* cmatrix2_inverse(CMatrix2* obj, CMatrix2* outInverse, CVMFloat *outDeterminant);

//     col 0 1 2 3
// row
//   0
//   1
//   2
//   3
CVMFloat cmatrix2_getValue(CMatrix2* obj, int row, int col);
void cmatrix2_show(CMatrix2* obj);


//
//
// RAW
//
//
CMatrix2RawRef cmatrix2raw_setIdentity(CMatrix2RawRef obj);

CMatrix2RawRef cmatrix2raw_setValues(CMatrix2RawRef obj,
              CVMFloat a11, CVMFloat a12,
              CVMFloat a21, CVMFloat a22);
CMatrix2RawRef cmatrix2raw_copy(CMatrix2RawRef obj, CMatrix2RawRef out);
CMatrix2RawRef cmatrix2raw_add(CMatrix2RawRef obj, CMatrix2RawRef arg, CMatrix2RawRef out);
CMatrix2RawRef cmatrix2raw_sub(CMatrix2RawRef obj, CMatrix2RawRef arg, CMatrix2RawRef out);
CMatrix2RawRef cmatrix2raw_mul(CMatrix2RawRef obj, CMatrix2RawRef arg, CMatrix2RawRef out);
CVector2RawRef cmatrix2raw_mulVector2Raw(CMatrix2RawRef obj, CVector2RawRef arg, CVector2RawRef out);
CVector2RawRef cmatrix2raw_mulVector(CMatrix2RawRef obj, CVMFloat x, CVMFloat y, CVector2RawRef out);

CMatrix2RawRef cmatrix2raw_transpose(CMatrix2RawRef obj, CMatrix2RawRef out);
CVMFloat cmatrix2raw_determinant(CMatrix2RawRef obj);
CMatrix2RawRef cmatrix2raw_inverse(CMatrix2RawRef obj, CMatrix2RawRef outInverse, CVMFloat *outDeterminant);

CVMFloat cmatrix2raw_getValue(CMatrix2RawRef obj, int row, int col);
void cmatrix2raw_show(CMatrix2RawRef obj);
#endif
