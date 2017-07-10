
#ifndef __H_GL_MATRIX_
#define __H_GL_MATRIX_

typedef float KValue;
typedef KValue KMatrix[16];

KMatrix* newMatrix();
KMatrix* freeMatrix(KMatrix* obj);
KMatrix* setIdentity(KMatrix* obj);
KMatrix* setRotateX(KMatrix* obj, double angle);


KMatrix* add(KMatrix* obj, KMatrix* arg, KMatrix* out);
KMatrix* sub(KMatrix* obj, KMatrix* arg, KMatrix* out);
KMatrix* outer(KMatrix* obj, KMatrix* arg, KMatrix* out);
#endif
