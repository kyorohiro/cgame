#ifndef __H_CVector2
#define __H_CVector2

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvectorMath_inner.h"


typedef CVMFloat CVector2Raw[2];
typedef CVMFloat *CVector2RawRef;

typedef struct {
  CObject parent;
  CVector2Raw value;
} CVector2;

CVector2* newCVector2(CMemory*);
CVector2* initCVector2(CVector2*, CVMFloat v0, CVMFloat v1);
CVector2* createCVector2(CVMFloat v0, CVMFloat v1);

CVMFloat cvector2_crossProduct(CVector2* obj, CVector2* arg);
CVMFloat cvector2_dotProduct(CVector2* obj, CVector2* arg);
CVector2* cvector2_normalize(CVector2* obj, CVector2* out);
CVector2* cvector2_add(CVector2* obj, CVector2* arg, CVector2* out);
CVector2* cvector2_sub(CVector2* obj, CVector2* arg, CVector2* out);
CVector2* cvector2_mulScalar(CVector2* obj, CVMFloat v, CVector2* out);
CVector2* cvector2_divScalar(CVector2* obj, CVMFloat v, CVector2* out);
CVMFloat cvector2_distance(CVector2* obj, CVector2* arg);
CVMFloat cvector2_length(CVector2* obj);

void cvector2_show(CVector2* obj);


CVector2RawRef  cvector2raw_add(CVector2RawRef obj, CVector2RawRef arg, CVector2RawRef out);
CVMFloat cvector2raw_crossProduct(CVector2RawRef obj, CVector2RawRef arg);
CVMFloat cvector2raw_dotProduct(CVector2RawRef obj, CVector2RawRef arg);
CVector2RawRef cvector2raw_normalize(CVector2RawRef obj, CVector2RawRef out);
CVector2RawRef cvector2raw_add(CVector2RawRef obj, CVector2RawRef arg, CVector2RawRef out);
CVector2RawRef cvector2raw_sub(CVector2RawRef obj, CVector2RawRef arg, CVector2RawRef out);
CVector2RawRef cvector2raw_mulScalar(CVector2RawRef obj, CVMFloat v, CVector2RawRef out);
CVector2RawRef cvector2raw_divScalar(CVector2RawRef obj, CVMFloat v, CVector2RawRef out);
CVMFloat cvector2raw_distance(CVector2RawRef obj, CVector2RawRef v);
CVMFloat cvector2raw_length(CVector2RawRef obj);
void cvector2raw_show(CVector2RawRef obj);

#endif
