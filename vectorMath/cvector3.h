#ifndef __H_CVector3
#define __H_CVector3

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cmatrix_inner.h"


typedef CMatrixValueType CVector3Raw[3];
typedef CMatrixValueType *CVector3RawRef;

typedef struct {
  CObject parent;
  CVector3Raw value;
} CVector3;

CVector3* newCVector3(CMemory*);
CVector3* initCVector3(CVector3*, CMatrixValueType v0, CMatrixValueType v1, CMatrixValueType v2);
CVector3* createCVector3(CMatrixValueType v0, CMatrixValueType v1, CMatrixValueType v2);

CVector3* cvector3_crossProduct(CVector3* obj, CVector3* arg, CVector3* out);
CMatrixValueType cvector3_dotProduct(CVector3* obj, CVector3* arg);
CVector3* cvector3_normalize(CVector3* obj, CVector3* out);
CVector3* cvector3_add(CVector3* obj, CVector3* arg, CVector3* out);
CVector3* cvector3_sub(CVector3* obj, CVector3* arg, CVector3* out);
CVector3* cvector3_mulScalar(CVector3* obj, CMatrixValueType v, CVector3* out);
CVector3* cvector3_divScalar(CVector3* obj, CMatrixValueType v, CVector3* out);
CMatrixValueType cvector3_distance(CVector3* obj, CVector3* arg);
CMatrixValueType cvector3_length(CVector3* obj);

void cvector3_show(CVector3* obj);

CVector3RawRef cvector3raw_setValues(CVector3RawRef obj, CMatrixValueType x, CMatrixValueType y, CMatrixValueType z);
CVector3RawRef cvector3raw_crossProduct(CVector3RawRef obj, CVector3RawRef arg, CVector3RawRef out);
CMatrixValueType cvector3raw_dotProduct(CVector3RawRef obj, CVector3RawRef arg);
CVector3RawRef cvector3raw_normalize(CVector3RawRef obj, CVector3RawRef out);
CVector3RawRef cvector3raw_add(CVector3RawRef obj, CVector3RawRef arg, CVector3RawRef out);
CVector3RawRef cvector3raw_sub(CVector3RawRef obj, CVector3RawRef arg, CVector3RawRef out);
CVector3RawRef cvector3raw_mulScalar(CVector3RawRef obj, CMatrixValueType v, CVector3RawRef out);
CVector3RawRef cvector3raw_divScalar(CVector3RawRef obj, CMatrixValueType v, CVector3RawRef out);
CMatrixValueType cvector3raw_distance(CVector3RawRef obj, CVector3RawRef v);
CMatrixValueType cvector3raw_length(CVector3RawRef obj);
void cvector3raw_show(CVector3RawRef obj);

#endif
