#ifndef __H_CVector4
#define __H_CVector4

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvectorMath_inner.h"

typedef CVMFloat CVector4Raw[4];
typedef CVMFloat *CVector4RawRef;

typedef struct {
  CObject parent;
  CVector4Raw value;
} CVector4;

CVector4* newCVector4(CMemory*);
CVector4* initCVector4(CVector4*, CVMFloat v0, CVMFloat v1, CVMFloat v2, CVMFloat v3);
CVector4* createCVector4(CVMFloat v0, CVMFloat v1, CVMFloat v2, CVMFloat v3);

CVector4* cvector4_add(CVector4* obj, CVector4* arg, CVector4* out);
CVector4* cvector4_sub(CVector4* obj, CVector4* arg, CVector4* out);
CVector4* cvector4_mulScalar(CVector4* obj, CVMFloat v, CVector4* out);
CVector4* cvector4_divScalar(CVector4* obj, CVMFloat v, CVector4* out);
CVMFloat cvector4_dotProduct(CVector4* obj, CVector4* arg);

CVMFloat cvector4_length(CVector4* obj);
CVector4* cvector4_normalize(CVector4* obj, CVector4* out);
CVMFloat cvector4_distance(CVector4* obj, CVector4* arg);

void cvector4_show(CVector4* obj);

CVector4RawRef cvector4raw_setValues(CVector4RawRef obj, CVMFloat x, CVMFloat y, CVMFloat z, CVMFloat w);
CVector4RawRef cvector4raw_add(CVector4RawRef obj, CVector4RawRef arg, CVector4RawRef out);
CVector4RawRef cvector4raw_sub(CVector4RawRef obj, CVector4RawRef arg, CVector4RawRef out);
CVector4RawRef cvector4raw_mulScalar(CVector4RawRef obj, CVMFloat v, CVector4RawRef out);
CVector4RawRef cvector4raw_divScalar(CVector4RawRef obj, CVMFloat v, CVector4RawRef out);
CVMFloat cvector4raw_dotProduct(CVector4RawRef obj, CVector4RawRef arg);

CVMFloat cvector4raw_length(CVector4RawRef obj);
CVector4RawRef cvector4raw_normalize(CVector4RawRef obj, CVector4RawRef out);
CVMFloat cvector4raw_distance(CVector4RawRef obj, CVector4RawRef v);
void cvector4raw_show(CVector4RawRef obj);
#endif
