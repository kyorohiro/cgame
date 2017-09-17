#ifndef _H_CGAME
#define _H_CGAME

#include "core/cobject.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/carrayList.h"

#include "matrix/cray.h"

#include "app/capp.h"
#include "app/cglu.h"
#include "app/cdynaTexAtlas.h"

#include "cobject3d.h"
#include "ccamera3d.h"

#define CGAME_NAME "cga"

#ifndef RENDER_MODE
#define RENDER_MODE 1
#endif

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
  CRay* mouseRay;

  //
  // draw cache
  CArrayList *dynaTexList;
  CBytes* vertexes;
  CBytes* indexes;

  //
  // status
  int callInited;
  int callInnerInited;
} CGame;

//
// unused CGame is singleton
//
CGame* newCGame(CMemory* mem);
CGame* initCGame(CGame*, CApp*);
CGame* createCGame(int window, int height);
//
CGame* getCGame();
CGame* cgame_run(CGame*);
CGame* cgame_init(CGame*);

CObject3D* cgame_getRoot(CGame*);
CCamera3D* cgame_getCamera(CGame*);
CAppMouseEvent* cgame_getCurrentMouseEvent(CGame*);
CGame* cgame_postRedisplay(CGame*);
CRay* cgame_getMouseRay(CGame*);
CDynaTexAtlas* cgame_getCDynaTexAtlas(CGame* obj, int index);

//
//CObject3D* cobject3d_setOnEnterFrameFunc(CObject3D* obj, CObject3DFuncOnEnterFrame func);
CGame* cgame_setOnEnterFrameFunc(CGame* obj, CObject3DFuncOnEnterFrame func);


#endif
