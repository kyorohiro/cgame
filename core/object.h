#ifndef _H_OBJECT
#define _H_OBJECT
//typedef int (*free)(int n);
typedef struct {
  char name[12];
  int reference;
} CObject;

CObject* newObject(const char *name);
CObject* initObject(CObject*obj, const char *name);
CObject* freeObject(CObject* obj);
CObject* upCounter(CObject* obj);
CObject* downCounter(CObject* obj);
CObject* releaseObject(CObject* obj);
#endif
