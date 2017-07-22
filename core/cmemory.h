#ifndef _H_MALLOC
#define _H_MALLOC
//typedef int (*free)(int n);

typedef void* (*FuncCalloc)(void* obj,int num, int size);
typedef void (*FuncFree)(void* obj,void *ptr);

typedef struct {
  int callocCounter;
  int freeCounter;
  FuncCalloc calloc;
  FuncFree free;
  long index;
} CMemory;


CMemory* newCMemory();
CMemory* initCMemory(CMemory* obj);
void freeCMemory(CMemory* obj);

void* cmemory_calloc(CMemory*, int num, int size);
void cmemory_free(CMemory*, void *ptr);
CMemory* getCMemory();

#endif
