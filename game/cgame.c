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

CGame* newCGame(CMemory* mem) {
  CGame * ret = cmemory_calloc(mem, 1, sizeof(CGame));
  ret->parent.cmemory = mem;
  return ret;
}
CGame* initCGame(CGame* obj, CApp* appObj) {
  printf("initCGame\r\n");
  initCObject((CObject*)obj, CGAME_NAME);
  snprintf(obj->title, sizeof(obj->title), "%s", "title");
  obj->app = appObj;
  obj->width = 400;
  obj->height = 300;
  //
  #ifdef PLATFORM_EMCC
    char* fs = "/game/assets/fs.glsl";
    char* vs = "/game/assets/vs.glsl";
  #else
    char* fs = "./game/assets/fs.glsl";
    char* vs = "./game/assets/vs.glsl";
  #endif
  printf("load Shader\r\n");

  obj->fShaderSrc = cutil_newCStringFromPath(obj->parent.cmemory, fs);
  obj->vShaderSrc = cutil_newCStringFromPath(obj->parent.cmemory, vs);
  //printf("len = %d\r\n",cstring_getByteLength(obj->fShaderSrc));
  //
//  obj->root = initCObject3D(newCObject3D(obj->parent.cmemory));
  obj->root = (CObject3D*)initCRoot3D(newCRoot3D(obj->parent.cmemory), 100);
  //
  obj->funcFraw = NULL;
  obj->fShaderLocation = 0;
  obj->vShaderLocation = 0;
  obj->program = 0;
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


void cgame_draw(CObject *context, CObject *args) {
  //
  //
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  CGame *game = getCGame();
  CObject3D *root = (CObject3D*)cgame_getRoot(game);
  if(root == NULL) {
    printf("ROOT == NULL\r\n");
    return;
  }
  //
  CLinkedList *nodes = cobject3d_getNodes(root);
  glClear(GL_COLOR_BUFFER_BIT);
  if(nodes == NULL) {
    printf("NODES == NULL\r\n");
    return;
  }

  cobject3d_enterFrame(root, root, args);

  //
  // create Buffer
  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);

  GLuint indexBuffer;
  glGenBuffers(1, &indexBuffer);
  for(int i=0;i<clinkedList_getLength(nodes);i++) {
    CObject3D *node = (CObject3D*)clinkedList_get(nodes, i);
    if(node->type != CObject3DTypePrimitive) {
      continue;
    }
    GLfloat *vVertices = (GLfloat *)cprimitive3d_getVertexBinary((CPrimitive3D *)node);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CMatrixVertexType)*10*cprimitive3d_getVertexBinaryLength((CPrimitive3D *)node), vVertices, GL_STATIC_DRAW);
    glUseProgram(game->program);
    int vPositionLoc = glGetAttribLocation(game->program, "position");
    int vRotLoc      = glGetAttribLocation(game->program, "rot");
    int vColorLoc    = glGetAttribLocation(game->program, "color");
    int vNormalLoc    = glGetAttribLocation(game->program, "normal");
    int vCameraLoc = glGetUniformLocation(game->program, "camera");
    int vModelLoc = glGetUniformLocation(game->program, "model");
    glEnableVertexAttribArray(vPositionLoc);
    glEnableVertexAttribArray(vColorLoc);
    glEnableVertexAttribArray(vRotLoc);
    glEnableVertexAttribArray(vNormalLoc);
    glVertexAttribPointer(vPositionLoc, 3, GL_FLOAT, GL_FALSE, PRIMITIVE3D_BUFFER_SIZE * sizeof(CMatrixVertexType), (void*)0);
    glVertexAttribPointer(vColorLoc, 4, GL_FLOAT, GL_FALSE, PRIMITIVE3D_BUFFER_SIZE * sizeof(CMatrixVertexType), (void*)(3*sizeof(CMatrixVertexType)));
    glVertexAttribPointer(vRotLoc, 3, GL_FLOAT, GL_FALSE, PRIMITIVE3D_BUFFER_SIZE * sizeof(CMatrixVertexType), (void*)(7*sizeof(CMatrixVertexType)));
    glVertexAttribPointer(vNormalLoc, 3, GL_FLOAT, GL_FALSE, PRIMITIVE3D_BUFFER_SIZE * sizeof(CMatrixVertexType), (void*)(10*sizeof(CMatrixVertexType)));

    glUniformMatrix4fv(vModelLoc, 1, GL_FALSE, (GLfloat*)node->mat->value);
    glUniformMatrix4fv(vCameraLoc, 1, GL_FALSE, (GLfloat*)game->camera->mat->value);
//    printf("#\r\n");
//    cmatrix4_show(node->mat);
    short* indices = (short*)cprimitive3d_getIndexBinary((CPrimitive3D*)node);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CMatrixIndexType)*cprimitive3d_getIndexBinaryLength((CPrimitive3D*)node), indices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, cprimitive3d_getIndexBinaryLength((CPrimitive3D*)node), GL_UNSIGNED_SHORT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &indexBuffer);

  //glutSwapBuffers();
  //glutPostRedisplay();
//releaseCObject((CObject*)mat);
  //
  //
  capp_flushBuffers(game->app);


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

  gameObj->fShaderLocation = cglutil_LoadShader(GL_FRAGMENT_SHADER, cstring_getBytes(gameObj->fShaderSrc));
  gameObj->vShaderLocation = cglutil_LoadShader(GL_VERTEX_SHADER, cstring_getBytes(gameObj->vShaderSrc));
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
