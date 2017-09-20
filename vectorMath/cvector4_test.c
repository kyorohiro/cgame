#include <stdio.h>
#include "core/cbytes.h"
#include "core/cmemory.h"
#include "cmatrix4.h"
#include "cvector4.h"

void cvector4_test_add() {
  printf("# cvector4_test_add\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CVector4 *vec1 = initCVector4(newCVector4(mem), 1.0, 2.0, 3.0, 4.0);
  CVector4 *vec2 = initCVector4(newCVector4(mem), 5.0, 6.0, 7.0, 8.0);

  CVector4 *vec3 =cvector4_add(vec1, vec2, NULL);
  if(vec3->value[0] != 6.0 || vec3->value[1] != 8.0 || vec3->value[2] != 10.0 || vec3->value[3] != 12.0 ) {
    printf("  NG : failed to add \r\n");
    cvector4_show(vec3);
    passed = 0;
  }

  cvector4_sub(vec1, vec2, vec3);
  if(vec3->value[0] != -4.0 || vec3->value[1] != -4.0 || vec3->value[2] != -4.0 || vec3->value[3] != -4.0 ) {
    printf("  NG : failed to sub \r\n");
    cvector4_show(vec3);
    passed = 0;
  }

  CVector4 *vec5 =cvector4_mulScalar(vec1, 2.0, NULL);
  if(vec5->value[0] != 2.0 || vec5->value[1] != 4.0 || vec5->value[2] != 6.0 || vec5->value[3] != 8.0) {
    printf("  NG : failed to mul \r\n");
    cvector4_show(vec5);
    passed = 0;
  }

  cvector4_divScalar(vec5, 2.0, vec5);
  if(vec5->value[0] != 1.0 || vec5->value[1] != 2.0 || vec5->value[2] != 3.0 || vec5->value[3] != 4.0) {
    printf("  NG : failed to div \r\n");
    cvector4_show(vec5);
    passed = 0;
  }

  //
  // 1 2 3 4
  // 5 6 7 8
  // 5 12 21 32
  // 17 53 ->70
  CVMFloat x = cvector4_dotProduct(vec1, vec2);
  if(((int)x) != 70) {
    printf("  NG : failed to dotProduct %f \r\n", x);
    passed = 0;
  }

  //
  //
  // 1 2 3 4,
  // 5 6 7 8,
  // 4 4 4 4
  // 4*4*4 = 16*4 = 64
  // sqrt 64> 8
  //
  CVMFloat y = cvector4_distance(vec1, vec2);
  if(y != 8.0) {
    printf("  NG : failed to distance %f \r\n", y);
    passed = 0;
  }

  //
  //
  // 1 2 3 4,
  // 1 4 9 16
  // 5 25 > 30
  // sqrt 30
  //
  CVMFloat z = cvector4_length(vec1);
  if((int)(1000*z) != 5477) {
    printf("  NG : failed to distance %f \r\n", z);
    passed = 0;
  }



  releaseCObject((CObject*)vec1);
  releaseCObject((CObject*)vec2);
  releaseCObject((CObject*)vec3);
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
