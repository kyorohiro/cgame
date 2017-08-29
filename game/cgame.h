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
  char title[256];
  int width;
  int height;
  CGameFuncDraw funcFraw;
  CString* fShaderSrc;
  CString* vShaderSrc;
  int fShaderLocation;
  int vShaderLocation;
  int program;
  CObject3D *root;
  CObject3D *camera;
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
CVector4* cgame_getLocalPointFromGlobal(CGame*, double x, double y, double z, CMatrix4* opt, CVector4* out);
CGame* cgame_postRedisplay(CGame*);
#endif
