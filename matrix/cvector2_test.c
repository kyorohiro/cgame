#include <stdio.h>
#include <math.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix4.h"
#include "cvector2.h"

void cvector2_test_add() {
  printf("# cvector2_test_add\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CVector2 *vec1 = initCVector2(newCVector2(mem), 1.0, 2.0);
  CVector2 *vec2 = initCVector2(newCVector2(mem), 3.0, 4.0);

  if(vec1->value[0] != 1.0 || vec1->value[1] != 2.0 ) {
    printf("  NG : failed to init value \r\n");
    passed = 0;
  }

  CVector2 *vec3 =cvector2_add(vec1, vec2, NULL);

  if(vec3->value[0] != 4.0 || vec3->value[1] != 6.0 ) {
    printf("  NG : failed to add \r\n");
    cvector2_show(vec3);
    passed = 0;
  }

  CVector2 *vec4 = cvector2_sub(vec1, vec2, NULL);

  if(vec4->value[0] != -2.0 || vec4->value[1] != -2.0 ) {
    printf("  NG : failed to sub \r\n");

    cvector2_show(vec3);
    passed = 0;
  }
  CVector2 *vec5 =cvector2_mulScalar(vec1, 2.0, NULL);
  if(vec5->value[0] != 2.0 || vec5->value[1] != 4.0 ) {
    printf("  NG : failed to mul \r\n");
    cvector2_show(vec1);
    cvector2_show(vec2);
    cvector2_show(vec5);
    passed = 0;
  }

  releaseCObject((CObject*)vec1);
  releaseCObject((CObject*)vec2);
  releaseCObject((CObject*)vec3);
  releaseCObject((CObject*)vec4);
  releaseCObject((CObject*)vec5);
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
