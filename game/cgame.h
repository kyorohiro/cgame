#ifndef _H_CGAME
#define _H_CGAME
//typedef int (*free)(int n);

#include "core/object.h"
#include "core/cmemory.h"

#define CGAME_NAME "cga";

typedef struct {
  CObject parent;
  char title[256];
  int width;
  int height;
} CGame;

CGame* newCGame(CMemory* mem);
CGame* initCGame(CGame*, char* name,char* title, int width, int height);
CGame* cgame_start(CGame*);
#endif
