#ifndef _H_CGAME
#define _H_CGAME

#include "core/cobject.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/carrayList.h"

#include "vectorMath/cray.h"

#include "app/capp.h"
#include "app/cglu.h"
#include "app/cdynaTexAtlas.h"

#include "cobject3d.h"
#include "ccamera3d.h"
#define CGAME_SETTING_NAME "cgas"
#define CGAME_NAME "cga"

#ifndef RENDER_MODE
#define RENDER_MODE 1
#endif

typedef void (*CGameFuncDraw)(CObject* obj);

//
typedef struct {
  CObject parent;
  int textureSize;
  int textureNum;
  int width;
  int height;
} CGameSetting;

typedef struct {
  CObject parent;
  CApp* app;
  CGameFuncDraw funcFraw;
  //
  //
  int textureSize;
  int textureNum;

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
//
//
CGameSetting* newCGameSetting(CMemory* mem);
CGameSetting* initCGameSetting(CGameSetting*, int width, int height);
CGameSetting* createCGameSetting(int window, int height);
CGameSetting* cgameSetting_setTextureInfo(CGameSetting*, int textureSize, int textureNum);


//
// unused CGame is singleton
//
CGame* getCGame();
CGame* newCGame(CMemory* mem);
CGame* initCGame(CGame*, CApp*, int textureSize, int textureNum);

CGame* createCGame(int window, int height);
CGame* createCGameFromSetting(CGameSetting* setting);
CGame* cgame_init(CGame*);
CGame* cgame_run(CGame*);
CGame* cgame_postRedisplay(CGame*);

//
CObject3D* cgame_getRoot(CGame*);
CCamera3D* cgame_getCamera(CGame*);
CAppMouseEvent* cgame_getCurrentMouseEvent(CGame*);
CRay* cgame_getMouseRay(CGame*);
CDynaTexAtlas* cgame_getCDynaTexAtlas(CGame* obj, int index);
CDynaTexAtlas* cgame_getAndBakeCDynaTexAtlas(CGame* obj, int index);
//
CGame* cgame_setOnEnterFrameFunc(CGame* obj, CObject3DFuncOnEnterFrame func);


#endif
