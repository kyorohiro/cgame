#ifndef __H_CVector3
#define __H_CVector3

#include "core/cobject.h"
#include "core/cmemory.h"
#include "cvectorMath_inner.h"


typedef CVMFloat CVector3Raw[3];
typedef CVMFloat *CVector3RawRef;

typedef struct {
  CObject parent;
  CVector3Raw value;
} CVector3;

CVector3* newCVector3(CMemory*);
CVector3* initCVector3(CVector3*, CVMFloat v0, CVMFloat v1, CVMFloat v2);
CVector3* createCVector3(CVMFloat v0, CVMFloat v1, CVMFloat v2);

CVector3* cvector3_crossProduct(CVector3* obj, CVector3* arg, CVector3* out);
CVMFloat cvector3_dotProduct(CVector3* obj, CVector3* arg);
CVector3* cvector3_normalize(CVector3* obj, CVector3* out);
CVector3* cvector3_add(CVector3* obj, CVector3* arg, CVector3* out);
CVector3* cvector3_sub(CVector3* obj, CVector3* arg, CVector3* out);
CVector3* cvector3_mulScalar(CVector3* obj, CVMFloat v, CVector3* out);
CVector3* cvector3_divScalar(CVector3* obj, CVMFloat v, CVector3* out);
CVMFloat cvector3_distance(CVector3* obj, CVector3* arg);
CVMFloat cvector3_length(CVector3* obj);

void cvector3_show(CVector3* obj);

CVector3RawRef cvector3raw_setValues(CVector3RawRef obj, CVMFloat x, CVMFloat y, CVMFloat z);
CVector3RawRef cvector3raw_crossProduct(CVector3RawRef obj, CVector3RawRef arg, CVector3RawRef out);
CVMFloat cvector3raw_dotProduct(CVector3RawRef obj, CVector3RawRef arg);
CVector3RawRef cvector3raw_normalize(CVector3RawRef obj, CVector3RawRef out);
CVector3RawRef cvector3raw_add(CVector3RawRef obj, CVector3RawRef arg, CVector3RawRef out);
CVector3RawRef cvector3raw_sub(CVector3RawRef obj, CVector3RawRef arg, CVector3RawRef out);
CVector3RawRef cvector3raw_mulScalar(CVector3RawRef obj, CVMFloat v, CVector3RawRef out);
CVector3RawRef cvector3raw_divScalar(CVector3RawRef obj, CVMFloat v, CVector3RawRef out);
CVMFloat cvector3raw_distance(CVector3RawRef obj, CVector3RawRef v);
CVMFloat cvector3raw_length(CVector3RawRef obj);
void cvector3raw_show(CVector3RawRef obj);

#endif
