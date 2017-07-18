#ifndef _H_CGAME
#define _H_CGAME
//typedef int (*free)(int n);

#include "core/object.h"
#include "core/cmemory.h"

#define CGAME_NAME "cga";

typedef void (*CGameFuncDraw)(CObject* obj);
typedef struct {
  CObject parent;
  char title[256];
  int width;
  int height;
  CGameFuncDraw funcFraw;
} CGame;

//
// unused CGame is singleton
//
CGame* newCGame(CMemory* mem);
//char* title, int width, int height
CGame* initCGame(CGame*, char* name);

//
CGame* getCGame();
CGame* cgame_start(CGame*);
#endif
