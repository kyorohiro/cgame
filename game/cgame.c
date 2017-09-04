#include "cgame.h"
#include "ccamera3d.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/cbytesBuilder.h"

#include "cglutil.h"
#include "cprimitive3d.h"
#include "croot3d.h"
#include "app/capp.h"
#include "matrix/cray.h"

//
void cgame_draw(CObject *context, CObject *args);
void cgame_init(CObject *context, CObject *args);
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

CGame* initCGame(CGame* obj, CApp* appObj) {
  printf("initCGame\r\n");
  CMemory *memory = (CMemory*)cobject_getCMemory((CObject*)obj);

  initCObject((CObject*)obj, CGAME_NAME);
  obj->app = appObj;

  //
  // shader
  #ifdef PLATFORM_EMCC
    #if RENDER_MODE == 0
    char* fs = "/game/assets/fs_ume.glsl";
    char* vs = "/game/assets/vs_ume.glsl";
    #else
    char* fs = "/game/assets/fs_matu.glsl";
    char* vs = "/game/assets/vs_matu.glsl";
    #endif
  #else
    #if RENDER_MODE == 0
    char* fs = "./game/assets/fs_ume.glsl";
    char* vs = "./game/assets/vs_ume.glsl";
    #else
    char* fs = "./game/assets/fs.glsl";
    char* vs = "./game/assets/vs.glsl";
    #endif
  #endif
  obj->program = 0;
  obj->fShaderLocation = 0;
  obj->vShaderLocation = 0;
  obj->fShaderSrc = cutil_newCStringFromPath(obj->parent.cmemory, fs);
  obj->vShaderSrc = cutil_newCStringFromPath(obj->parent.cmemory, vs);

  //
  // game draw cache
  obj->vertexes = initCBytes(newCBytes(obj->parent.cmemory), NULL, sizeof(CMatrixVertexType)*PRIMITIVE3D_BUFFER_SIZE*500);
  obj->indexes = initCBytes(newCBytes(obj->parent.cmemory), NULL, sizeof(CMatrixIndexType)*500);

  //
  //
  obj->camera = (CObject3D*)initCCamera3D(newCCamera3D(obj->parent.cmemory));
  obj->root = (CObject3D*)initCRoot3D(newCRoot3D(obj->parent.cmemory), 100);
  obj->funcFraw = NULL;

  //
  // event
  capp_addDisplayEventListener(appObj, (CObject*)obj, cgame_draw);
  capp_addInitEventListener(appObj, (CObject*)obj, cgame_init);

  //
  //
  obj->mouseRay = initCRay(newCRay(memory), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

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
    defaultCGame = initCGame(
      newCGame(getCMemory()),getCApp()
    );
  }
  return defaultCGame;
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

CGame* cgame_start(CGame* obj) {
  printf("## cgame_start\n");
  #if RENDER_MODE == 0
  printf("## ume\n");
  #else
  printf("## matu\n");
  #endif
  CApp* appObj = getCApp();

  capp_run(appObj);
  return obj;
}

void cgame_init(CObject *context, CObject *args) {
  printf("#1# cgame_init\n");

  CGame* gameObj = (CGame*)context;
  CApp* appObj = gameObj->app;

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
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.9f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  //
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
