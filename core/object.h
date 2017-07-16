#ifndef _H_OBJECT
#define _H_OBJECT
//typedef int (*free)(int n);

#define COBJECT_MODE_FREEABLE 0x01

typedef void (*FuncFreeObj)(void *obj);
typedef struct {
  char name[12];
  int reference;
  int mode;
  int index;
  FuncFreeObj funcFreeObj;
} CObject;

CObject* newCObject();
CObject* initCObject(CObject*obj, const char *name);
void freeCObject(void* obj);
CObject* upCounter(CObject* obj);
CObject* downCounter(CObject* obj);
CObject* releaseCObject(CObject* obj);
CObject* onMode(CObject* obj, int mode);
CObject* offMode(CObject* obj, int mode);
int getMode(CObject* obj, int mode);
#endif
