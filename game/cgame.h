#ifndef _H_CGAME
#define _H_CGAME
//typedef int (*free)(int n);

#include "core/cobject.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "app/capp.h"
#include "app/cglu.h"
#include "cobject3d.h"
#include "ccamera3d.h"



#define CGAME_NAME "cga"

typedef void (*CGameFuncDraw)(CObject* obj);
typedef struct {
  CObject parent;
  CApp* app;
  CGameFuncDraw funcFraw;

  //
  // shader
  int program;
  int fShaderLocation;
  int vShaderLocation;
  CString* fShaderSrc;
  CString* vShaderSrc;

  //
  // basic primitive
  CObject3D *root;
  CObject3D *camera;

  //
  // draw cache
  CBytes *vertexes;
  CBytes *indexes;
} CGame;

//
// unused CGame is singleton
//
CGame* newCGame(CMemory* mem);
CGame* initCGame(CGame*, CApp*);

//
CGame* getCGame();
CGame* cgame_start(CGame*);

CObject3D* cgame_getRoot(CGame*);
CCamera3D* cgame_getCamera(CGame*);
CAppMouseEvent* cgame_getCurrentMouseEvent(CGame*);
CGame* cgame_postRedisplay(CGame*);
#endif
