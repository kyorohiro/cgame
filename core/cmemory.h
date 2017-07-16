#ifndef _H_MALLOC
#define _H_MALLOC
//typedef int (*free)(int n);

typedef void* (*FuncCalloc)(int num, int size);
typedef void (*FuncFree)(void *ptr);

typedef struct {
  FuncCalloc calloc;
  FuncFree free;
} CMemory;


CMemory* newCMemory();
CMemory* initCMemory(CMemory* obj);
void freeCMemory(CMemory* obj);
#endif
