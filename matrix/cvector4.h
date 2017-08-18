#ifndef __H_GL_VECTOR4_
#define __H_GL_VECTOR4_

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cmatrix_inner.h"
#define KVECTOR4_NAME "ve4"

typedef CMatrixValueType CVector4Raw[4];
typedef CMatrixValueType *CVector4RawRef;

typedef struct {
  CObject parent;
  CVector4Raw value;
} CVector4;

CVector4* newCVector4(CMemory*);
CVector4* initCVector4(CVector4*, CMatrixVertexType v0, CMatrixVertexType v1, CMatrixVertexType v2, CMatrixVertexType v3);

CVector4* cvector4_add(CVector4* obj, CVector4* arg, CVector4* out);
CVector4* cvector4_sub(CVector4* obj, CVector4* arg, CVector4* out);
CVector4* cvector4_mulScalar(CVector4* obj, CMatrixValueType v, CVector4* out);
CVector4* cvector4_divScalar(CVector4* obj, CMatrixValueType v, CVector4* out);
CMatrixValueType cvector4_dotProduct(CVector4* obj, CVector4* arg);

CMatrixValueType cvector4_length(CVector4* obj);
CMatrixValueType cvector4_distance(CVector4* obj, CVector4* arg);

void cvector4_show(CVector4* obj);


CVector4RawRef cvector4raw_add(CVector4RawRef obj, CVector4RawRef arg, CVector4RawRef out);
CVector4RawRef cvector4raw_sub(CVector4RawRef obj, CVector4RawRef arg, CVector4RawRef out);
CVector4RawRef cvector4raw_mulScalar(CVector4RawRef obj, CMatrixValueType v, CVector4RawRef out);
CVector4RawRef cvector4raw_divScalar(CVector4RawRef obj, CMatrixValueType v, CVector4RawRef out);
CMatrixValueType cvector4raw_dotProduct(CVector4RawRef obj, CVector4RawRef arg);

CMatrixValueType cvector4raw_length(CVector4RawRef obj);
CVector4RawRef cvector4raw_normalize(CVector4RawRef obj, CVector4RawRef out);
CMatrixValueType cvector4raw_distance(CVector4RawRef obj, CVector4RawRef v);
void cvector4raw_show(CVector4RawRef obj);
#endif
