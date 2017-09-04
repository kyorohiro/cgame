#include "cgame.h"
#include "ccamera3d.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/cbytesBuilder.h"

#include "cglutil.h"
#include "cprimitive3d.h"
#include "croot3d.h"
#include "app/capp.h"

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
  initCObject((CObject*)obj, CGAME_NAME);
  obj->app = appObj;

  //
  // shader
  #ifdef PLATFORM_EMCC
    char* fs = "/game/assets/fs.glsl";
    char* vs = "/game/assets/vs.glsl";
  #else
    char* fs = "./game/assets/fs.glsl";
    char* vs = "./game/assets/vs.glsl";
  #endif
  obj->fShaderSrc = cutil_newCStringFromPath(obj->parent.cmemory, fs);
  obj->vShaderSrc = cutil_newCStringFromPath(obj->parent.cmemory, vs);
  obj->root = (CObject3D*)initCRoot3D(newCRoot3D(obj->parent.cmemory), 100);
  //
  obj->funcFraw = NULL;
  obj->fShaderLocation = 0;
  obj->vShaderLocation = 0;
  obj->program = 0;

  //
  //
  obj->vertexes = initCBytes(newCBytes(obj->parent.cmemory), NULL, sizeof(CMatrixVertexType)*PRIMITIVE3D_BUFFER_SIZE*500);
  obj->indexes = initCBytes(newCBytes(obj->parent.cmemory), NULL, sizeof(CMatrixIndexType)*500);

  //
  //
  obj->camera = (CObject3D*)initCCamera3D(newCCamera3D(obj->parent.cmemory));

  //
  //
  capp_addDisplayEventListener(appObj, (CObject*)obj, cgame_draw);
  capp_addInitEventListener(appObj, (CObject*)obj, cgame_init);
  printf("[ASOS OK]\r\n");

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

void cgame_draw02(CObject *context, CObject *args) {

}


void cgame_draw(CObject *context, CObject *args) {
  cgame_draw_matu(context, args);
}

CGame* cgame_start(CGame* obj) {
  printf("## cgame_start\n");
  CApp* appObj = getCApp();

  capp_run(appObj);
  return obj;
}

void cgame_init(CObject *context, CObject *args) {
  printf("#1# cgame_init\n");

  CGame* gameObj = getCGame();
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


CAppMouseEvent* cgame_getCurrentMouseEvent(CGame* obj) {
  return capp_getCurrentMouseEvent(getCApp());
}

CGame* cgame_postRedisplay(CGame* obj) {
  capp_postRedisplay(obj->app);
  return obj;
}

CVector4* cgame_getLocalPointFromGlobal(CGame* obj, double x, double y, double z, CMatrix4* in, CVector4* out) {
//CVector4* cgame_getLocalPointFromGlobal(CGame* obj, double x, double y, CVector4* out) {
  CMemory *mem = cobject_getCMemory((CObject*)obj);
  CRoot3D *root = (CRoot3D*)cgame_getRoot(obj);
  CCamera3D *camera = (CCamera3D*)cgame_getCamera(obj);
  CMatrix4 *model = croot3d_peekMulMatrix(root);
  CMatrix4 *mat = cmatrix4_mul(camera->parent.mat, model, NULL);

  if(in != NULL) {
    cmatrix4_mul(mat, in, mat);
  }
  cmatrix4_inverse(mat, mat, NULL);


  //
  //
  if(out == NULL) {
    out = initCVector4(newCVector4(mem), x, y, z, 1.0);
  } else {
    out->value[0] = x;
    out->value[1] = y;
    out->value[2] = 0.0;
    out->value[3] = 1.0;
  }

  cmatrix4_mulCVector4(mat, out, out);

  releaseCObject((CObject*)mat);
  return out;
}
