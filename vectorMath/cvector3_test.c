#include <stdio.h>
#include <math.h>
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
    printf("  NG : failed to add \r\n");
    cvector3_show(vec3);
    passed = 0;
  }

  CVector3 *vec4 =cvector3_sub(vec1, vec2, NULL);

  if(vec4->value[0] != -5.0 || vec4->value[1] != -3.0 || vec4->value[2] != -1.0 ) {
    printf("  NG : failed to sub \r\n");
    cvector3_show(vec3);
    passed = 0;
  }

  //

  CVector3 *vec5 =cvector3_mulScalar(vec1, 2.0, NULL);
  if(vec5->value[0] != 2.0 || vec5->value[1] != 4.0 || vec5->value[2] != 6.0 ) {
    printf("  NG : failed to mul \r\n");
    cvector3_show(vec1);
    cvector3_show(vec2);
    cvector3_show(vec5);
    passed = 0;
  }

  cvector3_divScalar(vec5, 2.0, vec5);
  if(vec5->value[0] != 1.0 || vec5->value[1] != 2.0 || vec5->value[2] != 3.0) {
    printf("  NG : failed to div \r\n");
    cvector3_show(vec1);
    cvector3_show(vec2);
    cvector3_show(vec5);
    passed = 0;
  }


  CVector3 *vec6 = initCVector3(newCVector3(mem), 1.0, 3.0, -5.0);
  CVector3 *vec7 = initCVector3(newCVector3(mem), 4.0, -2.0, -1.0);
  CVMFloat x = cvector3_dotProduct(vec6, vec7);
  if(((int)x) != 3) {
    printf("  NG : failed to dotProduct %d \r\n", (int)x);
    passed = 0;
  }

  CVector3 *vec8 = initCVector3(newCVector3(mem), 0.417267069084370, 0.049654430325742, 0.902716109915281);
  CVector3 *vec9 = initCVector3(newCVector3(mem), 0.944787189721646,0.490864092468080, 0.489252638400019);
  CVector3 *vec10 = cvector3_crossProduct(vec8, vec9, NULL);

  //-0.418817 0.648726 0.157909
  if( (int)(vec10->value[0]*1000) != -418 ||
      (int)(vec10->value[1]*1000) != 648 ||
      (int)(vec10->value[2]*1000) != 157 )
  {
    printf("  NG : failed to dotProduct %d %d %d\r\n", ((int)vec10->value[0]*1000), ((int)vec10->value[1]*1000), ((int)vec10->value[2]*1000));
    cvector3_show(vec10);
    passed = 0;
  }

  //
  // 1 2 3, 6 5 4
  // 5*5 3*3 1*1
  // sqrt 25+9+1 > 35
  //
  CVMFloat d = cvector3_distance(vec1, vec2);
  if((int)(d*1000) != 5916) {
    printf("  NG : failed to distance %f \r\n", d);
    passed = 0;
  }


  //
  // 1 2 3 -> sqrt(1+4+9)
  //
  CVMFloat e = cvector3_length(vec1);
  if((int)(e*1000) != 3741) {
    printf("  NG : failed to length %f \r\n", e);
    passed = 0;
  }

  CVector3 *vec11 = cvector3_normalize(vec1, NULL);
  if((int)(vec11->value[0]*1000) != (int)(vec1->value[0]/e*1000) ||
    (int)(vec11->value[1]*1000) != (int)(vec1->value[1]/e*1000) ||
    (int)(vec11->value[2]*1000) != (int)(vec1->value[2]/e*1000)) {
    printf("  NG : failed to normalize %f %f \r\n", vec11->value[0], vec1->value[0]/e);
    cvector3_show(vec11);
    passed = 0;
  }

  releaseCObject((CObject*)vec1);
  releaseCObject((CObject*)vec2);
  releaseCObject((CObject*)vec3);
  releaseCObject((CObject*)vec4);
  releaseCObject((CObject*)vec5);
  releaseCObject((CObject*)vec6);
  releaseCObject((CObject*)vec7);
  releaseCObject((CObject*)vec8);
  releaseCObject((CObject*)vec9);
  releaseCObject((CObject*)vec10);
  releaseCObject((CObject*)vec11);

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

void cvector3_test_normalize() {
  printf("# cvector3_test_normalize\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CVector3 *vec1 = initCVector3(newCVector3(mem), 5.0, 7.0, 3.0);

  if(vec1->value[0] != 5.0 || vec1->value[1] != 7.0 || vec1->value[2] != 3.0 ) {
    printf("  NG : failed to init value \r\n");
    passed = 0;
  }

  CVMFloat v = cvector3_length(vec1);
  if(  floor(v*10000)/10000 != 9.1104 ) {
    printf("  NG : failed to length%f \r\n", floor(v*1000)/1000);
    passed = 0;
  }

  releaseCObject((CObject*)vec1);

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

void cvector3_test_dotProduct() {
  printf("# cvector3_test_dotProduct\n");
  int passed = 1;
  CMemory *mem = initCMemory(newCMemory());
  CVector3 *vec1 = initCVector3(newCVector3(mem), 0.417267069084370, 0.049654430325742, 0.902716109915281);
  CVector3 *vec2 = initCVector3(newCVector3(mem), 0.944787189721646, 0.490864092468080, 0.489252638400019);


  CVMFloat v = cvector3_dotProduct(vec1, vec2);

  if(  floor(v*1000)/1000 != 0.860 )
  {
    printf("  NG : failed to normalize %f \r\n", floor(v*1000)/1000);
    passed = 0;
  }

  releaseCObject((CObject*)vec1);
  releaseCObject((CObject*)vec2);

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
