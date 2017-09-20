#include <stdio.h>
#include <math.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix4.h"
#include "cray.h"
#include "vectorMath/cmatrix_proj.h"


void cmatrix4_test_ray() {
  printf("# cmatrix4_test_ray\n");

  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CRay *ray = initCRay(newCRay(mem),
    1.0, 1.0, 1.0,
    0.0, 1.0, 0.0);

  {
    CVector3Raw v1; v1[0]=2.0;v1[1]=2.0;v1[2]= 0.0;
    CVector3Raw v2; v2[0]=0.0;v2[1]=4.0;v2[2]= -1.0;
    CVector3Raw v3; v3[0]=0.0;v3[1]=4.0;v3[2]= 3.0;
    double d = crayraw_intersectsWithTriangle(ray->origin->value, ray->direction->value, v1, v3, v2);

    printf("#1# %lf \r\n", d);
  }

  {
    CVector3Raw v1; v1[0]=0.0;v1[1]=1.5;v1[2]= 1.0;
    CVector3Raw v2; v2[0]=2.0;v2[1]=1.5;v2[2]= 1.0;
    CVector3Raw v3; v3[0]=1.0;v3[1]=1.5;v3[2]= 3.0;
    double dd = crayraw_intersectsWithTriangle(ray->origin->value, ray->direction->value, v1, v3, v2);
    printf("#2# %lf \r\n", dd);
  }
  {
    CVector3Raw v1; v1[0]=2.0;v1[1]=2.0;v1[2]= 0.0;
    CVector3Raw v2; v2[0]=2.0;v2[1]=6.0;v2[2]= 0.0;
    CVector3Raw v3; v3[0]=2.0;v3[1]=2.0;v3[2]= 3.0;
    double d = crayraw_intersectsWithTriangle(ray->origin->value, ray->direction->value, v1, v3, v2);
    printf("#3# %lf \r\n", d);
  }

  {
    CVector3Raw v1; v1[0]=0.0;v1[1]=0.0;v1[2]= 0.0;
    CVector3Raw v2; v2[0]=0.0;v2[1]=3.0;v2[2]= 0.0;
    CVector3Raw v3; v3[0]=0.0;v3[1]=3.0;v3[2]= 4.0;
    double d = crayraw_intersectsWithTriangle(ray->origin->value, ray->direction->value, v1, v3, v2);
    printf("#4# %lf \r\n", d);
  }


  releaseCObject((CObject*)ray);

  if(mem->callocCounter != mem->freeCounter) {
    printf("  NG : %d == %d\r\n", mem->callocCounter, mem->freeCounter);
    passed = 0;
  }

  freeCMemory(mem);
  if(passed) {
    printf("  OK : \r\n");
  }
  printf("\r\n\r\n");
}


void cmatrix4_test_ray2() {
  printf("# cmatrix4_test_ray2\n");

  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CRay *ray = initCRay(newCRay(mem),
    0.0, 1.0, 0.0,
    0.0, 0.0, -1.0);

  CVector3Raw v1; v1[0]=-1.0;v1[1]=2.0;v1[2]= -1.0;
  CVector3Raw v2; v2[0]=2.0;v2[1]=2.0;v2[2]= -1.0;
  CVector3Raw v3; v3[0]=2.0;v3[1]=-2*2.0;v3[2]= -1.0;
  double d = crayraw_intersectsWithTriangle(ray->origin->value, ray->direction->value, v1, v3, v2);

  printf("#1# %lf \r\n", d);

  releaseCObject((CObject*)ray);

  if(mem->callocCounter != mem->freeCounter) {
    printf("  NG : %d == %d\r\n", mem->callocCounter, mem->freeCounter);
    passed = 0;
  }

  freeCMemory(mem);
  if(passed) {
    printf("  OK : \r\n");
  }
  printf("\r\n\r\n");
}
