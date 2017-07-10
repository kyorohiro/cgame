#ifndef _H_LIST

//typedef int (*free)(int n);
typedef CObject *pCObject;
typedef struct {
  CObject parent;
  int length;
  CObject **objects;
} ArrayList;

ArrayList* newArrayList(const char *name);
ArrayList* freeArrayList(CObject* obj);
#endif
