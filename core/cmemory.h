#ifndef _H_CMemory
#define _H_CMemory

typedef void* (*FuncCalloc)(void* obj,int num, int size);
typedef void (*FuncFree)(void* obj,void *ptr);

typedef struct {
  long counter;
  int callocCounter;
  int freeCounter;
  FuncCalloc calloc;
  FuncFree free;
} CMemory;

CMemory* newCMemory();
CMemory* initCMemory(CMemory* obj);
CMemory* getCMemory();
void freeCMemory(CMemory* obj);

void* cmemory_calloc(CMemory*, int num, int size);
void cmemory_free(CMemory*, void *ptr);
long cmemory_getUId(CMemory*);


#endif
