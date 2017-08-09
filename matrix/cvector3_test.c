#include <stdio.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix4.h"
#include "cvector3.h"

void cvector3_test_add() {
  printf("# cvector3_test_add\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CVector3 *vec1 = initCVector3(newCVector3(mem), 1.0, 2.0, 3.0);
  CVector3 *vec2 = initCVector3(newCVector3(mem), 6.0, 5.0, 4.0);

  if(vec1->value[0] != 1.0 || vec1->value[1] != 2.0 || vec1->value[2] != 3.0 ) {
    printf("  NG : failed to init value \r\n");
    passed = 0;
  }

  CVector3 *vec3 =cvector3_add(vec1, vec2, NULL);

  if(vec3->value[0] != 7.0 || vec3->value[1] != 7.0 || vec3->value[2] != 7.0 ) {
    printf("  NG : failed to init value \r\n");
    passed = 0;
  }

  CVector3 *vec4 =cvector3_sub(vec1, vec2, NULL);

  if(vec4->value[0] != -5.0 || vec4->value[1] != -3.0 || vec4->value[2] != -1.0 ) {
    printf("  NG : failed to init value \r\n");
    passed = 0;
  }
  releaseCObject((CObject*)vec1);
  releaseCObject((CObject*)vec2);
  releaseCObject((CObject*)vec3);
  releaseCObject((CObject*)vec4);
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
