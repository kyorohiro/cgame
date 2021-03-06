#include "cgame.h"
#include "ccamera3d.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/cbytesBuilder.h"

#include "app/cglu.h"
#include "cprimitive3d.h"
#include "croot3d.h"
#include "app/capp.h"
#include "vectorMath/cray.h"

//
//
CGameSetting* newCGameSetting(CMemory* mem) {
  CGameSetting* obj = cmemory_calloc(mem, 1, sizeof(CGameSetting));
  obj->parent.cmemory = mem;
  obj->parent.funcFree = freeCObject;
  return obj;
}

CGameSetting* initCGameSetting(CGameSetting* obj, int width, int height) {
  initCObject((CObject*)obj, CGAME_SETTING_NAME);
  obj->width = width;
  obj->height = height;
  obj->textureNum = 1;
  obj->textureSize = 1024;
  return obj;
}

CGameSetting* createCGameSetting(int width, int height) {
  return initCGameSetting(newCGameSetting(getCMemory()), width, height);
}

CGameSetting* cgameSetting_setTextureInfo(CGameSetting* obj, int textureSize, int textureNum) {
  obj->textureNum = textureNum;
  obj->textureSize = textureSize;
  return obj;
}

//
void cgame_draw(CObject *context, CObject *args);
void cgame_init_inner(CObject *context, CObject *args);
void _freeCGame(void* obj);
void cgame_draw_matu(CObject *context, CObject *args);
void cgame_draw_ume(CObject *context, CObject *args);

CGame* newCGame(CMemory* mem) {
  CGame * ret = cmemory_calloc(mem, 1, sizeof(CGame));
  ret->parent.cmemory = mem;
  ret->parent.funcFree = _freeCGame;
  return ret;
}

void _freeCGame(void* obj) {
  if(obj == NULL) {
    return;
  }
  freeCObject(obj);
}

CGame* initCGame(CGame* obj, CApp* appObj, int textureSize, int textureNum) {
  printf("initCGame\r\n");
  CMemory *memory = (CMemory*)cobject_getCMemory((CObject*)obj);
  initCObject((CObject*)obj, CGAME_NAME);
  obj->app = appObj;
  obj->textureNum = textureNum;
  obj->textureSize = textureSize;

  //
  // shader
  #if RENDER_MODE == 0
  char* fs = capp_getAssetsPath(appObj, "game/assets/fs_ume.glsl", NULL);
  char* vs = capp_getAssetsPath(appObj, "game/assets/vs_ume.glsl", NULL);
  #else
  char* fs = capp_getAssetsPath(appObj, "game/assets/fs_matu.glsl", NULL);
  char* vs = capp_getAssetsPath(appObj, "game/assets/vs_matu.glsl", NULL);
  #endif

  obj->program = 0;
  obj->fShaderLocation = 0;
  obj->vShaderLocation = 0;
  obj->fShaderSrc = cutil_newCStringFromPath(obj->parent.cmemory, fs);
  obj->vShaderSrc = cutil_newCStringFromPath(obj->parent.cmemory, vs);

  //
  // game draw cache
  obj->vertexes = initCBytes(newCBytes(obj->parent.cmemory), NULL, sizeof(CMatrixVertexType)*PRIMITIVE3D_BUFFER_SIZE*1500);
  obj->indexes = initCBytes(newCBytes(obj->parent.cmemory), NULL, sizeof(CMatrixIndexType)*1500);

  //
  //
  obj->camera = (CObject3D*)initCCamera3D(newCCamera3D(obj->parent.cmemory));
  obj->root = (CObject3D*)initCRoot3D(newCRoot3D(obj->parent.cmemory), 100);
  obj->funcFraw = NULL;

  //
  // event
  capp_addDisplayEventListener(appObj, (CObject*)obj, cgame_draw);
  capp_addInitEventListener(appObj, (CObject*)obj, cgame_init_inner);

  //
  //
  obj->mouseRay = initCRay(newCRay(memory), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

  //
 obj->dynaTexList = initCArrayList(newCArrayList(memory), 16);

  return obj;
}

CObject3D* cgame_getRoot(CGame* obj) {
  return obj->root;
}

CCamera3D* cgame_getCamera(CGame* obj) {
  return (CCamera3D*)obj->camera;
}

CGame* defaultCGame = NULL;
CGame* getCGame() {
  if(defaultCGame == NULL) {
    defaultCGame = initCGame(newCGame(getCMemory()), getCApp(), 1024, 1);
    cgame_init(defaultCGame);
  }
  return defaultCGame;
}

CGame* createCGame(int window, int height) {
  CApp* app = createCApp(window, height);
  CGame* ret  = initCGame(newCGame(getCMemory()), app, 1024, 1);
  if(defaultCGame == NULL) {
    defaultCGame = ret;
  }
  cgame_init(defaultCGame);
  return ret;
}

CGame* createCGameFromSetting(CGameSetting* setting) {
  CApp* app = createCApp(setting->width, setting->height);
  CGame* ret  = initCGame(newCGame(getCMemory()), app, setting->textureSize, setting->textureNum);
  if(defaultCGame == NULL) {
    defaultCGame = ret;
  }
  cgame_init(defaultCGame);
  return ret;
}

CGame* cgame_setOnEnterFrameFunc(CGame* obj, CObject3DFuncOnEnterFrame func) {
  cobject3d_setOnEnterFrameFunc(obj->root, func);
  return obj;
}

void cgame_draw(CObject *context, CObject *args) {
  //
  // mouse ray
  CGame* gameObj = (CGame*)context;
  CApp* appObj = gameObj->app;
  CCamera3D* camera = cgame_getCamera(gameObj);
  CAppMouseEvent *event = cgame_getCurrentMouseEvent(gameObj);

  double mouseX = event->x - appObj->width/2;
  double mouseY = event->y - appObj->height/2;


  CMatrix4Raw tmp;
  CVector3Raw out2;
  cmatrix4raw_mul(camera->projection->value, camera->view->value, tmp);
  cmatrix4raw_unproject(tmp, -mouseX, appObj->width, mouseY, appObj->height, appObj->width/2, appObj->height/2, 1.0, out2);
  //cvector3raw_show(out2);

  //
  CVector3Raw ori;
  CVector3Raw dir;
  cvector3raw_setValues(ori, 0.0, 0.0, 5.0);
  cvector3raw_sub(out2, ori, dir);

  gameObj->mouseRay->direction->value[0] = dir[0];
  gameObj->mouseRay->direction->value[1] = dir[1];
  gameObj->mouseRay->direction->value[2] = dir[2];

  gameObj->mouseRay->origin->value[0] = ori[0];
  gameObj->mouseRay->origin->value[1] = ori[1];
  gameObj->mouseRay->origin->value[2] = ori[2];

#if RENDER_MODE == 0
  cgame_draw_ume(context, args);
#else
  cgame_draw_matu(context, args);
#endif
}

CGame* cgame_run(CGame* obj) {
  printf("## cgame_run %d \r\n", RENDER_MODE);
  CApp* appObj = getCApp();
  if(obj->callInited !=1) {
    capp_init(appObj);
  }
  capp_loop(appObj);
  return obj;
}

CGame* cgame_init(CGame* obj) {
  printf("## cgame_run %d \r\n", RENDER_MODE);
  CApp* appObj = getCApp();
  if(obj->callInited != 1) {
    capp_init(appObj);
    obj->callInited = 1;
  }
  return obj;
}


void cgame_init_inner(CObject *context, CObject *args) {
  printf("#1# cgame_init_inner\n");
  CGame* gameObj = (CGame*)context;
  CApp* appObj = gameObj->app;
  CMemory* memory = cobject_getCMemory(context);

  GLint m_maxTextureSize = 0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_maxTextureSize);

  int MaxUnitNum;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS,&MaxUnitNum);
  printf("maxTexSize : %d %d %d %d\r\n", m_maxTextureSize, MaxUnitNum,
   gameObj->textureNum, gameObj->textureSize);
  //
  for(int i=0;i<gameObj->textureNum;i++) {
    if(m_maxTextureSize >= gameObj->textureNum) {
      carrayList_addLast(gameObj->dynaTexList, (CObject*)initCDynaTexAtlas(newCDynaTexAtlas(memory), gameObj->textureSize, gameObj->textureSize));
    } else {
      printf("Failed to create texture\r\n");
    }
  }
//  carrayList_addLast(gameObj->dynaTexList, (CObject*)initCDynaTexAtlas(newCDynaTexAtlas(memory), 512, 512));

  gameObj->fShaderLocation = cglu_loadShader(GL_FRAGMENT_SHADER, cstring_getBytes(gameObj->fShaderSrc));
  gameObj->vShaderLocation = cglu_loadShader(GL_VERTEX_SHADER, cstring_getBytes(gameObj->vShaderSrc));
  gameObj->program = glCreateProgram();
  glAttachShader(gameObj->program, gameObj->fShaderLocation);
  glAttachShader(gameObj->program, gameObj->vShaderLocation);
  glLinkProgram(gameObj->program);
  printf("main2\n");

  //
  glViewport(0, 0, appObj->width, appObj->height);
  glScissor(0, 0, appObj->width, appObj->height);
  //
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.9f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  //
  gameObj->callInnerInited = 1;
}

CRay* cgame_getMouseRay(CGame* obj) {
  return obj->mouseRay;
}

CAppMouseEvent* cgame_getCurrentMouseEvent(CGame* obj) {
  return capp_getCurrentMouseEvent(getCApp());
}

CGame* cgame_postRedisplay(CGame* obj) {
  capp_postRedisplay(obj->app);
  return obj;
}

CDynaTexAtlas* cgame_getCDynaTexAtlas(CGame* obj, int index) {
  return (CDynaTexAtlas*)carrayList_get(obj->dynaTexList, index);
}

CDynaTexAtlas* cgame_getAndBakeCDynaTexAtlas(CGame* obj, int index) {

  while(carrayList_getLength(obj->dynaTexList) > index) {
    carrayList_addLast(obj->dynaTexList, NULL);
  }

  CObject* item = carrayList_get(obj->dynaTexList, index);
  if(item == NULL) {
    CMemory* memory = cobject_getCMemory((CObject*)obj);
    item = (CObject*)initCDynaTexAtlas(newCDynaTexAtlas(memory), 1024, 1024);
    carrayList_set(obj->dynaTexList, index, item);
  }
  return (CDynaTexAtlas*)item;
}
