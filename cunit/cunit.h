#ifndef _H_CUNIT

typedef struct {
  char name[32];
  char message[32];
  int result;
} TestCase;

TestCase* newTestCase(const name) {
  TestCase *ret = calloc(1,sizeof(TestCase));
  ret->name = name;
  return ret;
}

void testCase_setResult(TestCase* obj) {
}

TestCase* freeTestCase(TestCase* obj) {
  free(obj);
}
#endif
