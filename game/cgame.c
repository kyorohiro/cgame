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

CGame* initCGame(CGame* obj) {
  initCObject((CObject*)obj, CGAME_NAME);
  snprintf(obj->title, sizeof(obj->title), "%s", "title");
  obj->width = 400;
  obj->height = 300;
  //
  obj->fShaderSrc = cutil_newCStringFromPath(obj->parent.cmemory, "/game/assets/fs.glsl");
  obj->vShaderSrc = cutil_newCStringFromPath(obj->parent.cmemory, "/game/assets/vs.glsl");
  //
//  obj->root = initCObject3D(newCObject3D(obj->parent.cmemory));
  obj->root = (CObject3D*)initCRoot3D(newCRoot3D(obj->parent.cmemory));
  //
  obj->funcFraw = NULL;
  obj->fShaderLocation = 0;
  obj->vShaderLocation = 0;
  obj->program = 0;
  obj->camera = (CObject3D*)initCCamera3D(newCCamera3D(obj->parent.cmemory));

  //
  //
  CApp* appObj = getCApp();
  CGame* gameObj = obj;
  capp_addDisplayEventListener(appObj, (CObject*)gameObj, cgame_draw);
  capp_addInitEventListener(appObj, (CObject*)gameObj, cgame_init);

  return obj;
}

CObject3D* cgame_getRoot(CGame* obj) {
  return obj->root;
}

CGame* defaultCGame = NULL;
CGame* getCGame() {
  if(defaultCGame == NULL) {
    defaultCGame = initCGame(newCGame(getCMemory()));
  }
  return defaultCGame;
}


void cgame_draw(CObject *context, CObject *args) {
  CGame *game = getCGame();
  CObject3D *root = (CObject3D*)cgame_getRoot(game);
  //
  cobject3d_enterFrame(root, (CObject*)game);
  CLinkedList *nodes = cobject3d_getNodes(root);

  glClear(GL_COLOR_BUFFER_BIT);

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(CMatrixValue)*10*cprimitive3d_getVertexBinaryLength((CPrimitive3D *)node), vVertices, GL_STATIC_DRAW);
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
    glVertexAttribPointer(vPositionLoc, 3, GL_FLOAT, GL_FALSE, PRIMITIVE3D_BUFFER_SIZE * sizeof(CMatrixValue), (void*)0);
    glVertexAttribPointer(vColorLoc, 4, GL_FLOAT, GL_FALSE, PRIMITIVE3D_BUFFER_SIZE * sizeof(CMatrixValue), (void*)(3*sizeof(CMatrixValue)));
    glVertexAttribPointer(vRotLoc, 3, GL_FLOAT, GL_FALSE, PRIMITIVE3D_BUFFER_SIZE * sizeof(CMatrixValue), (void*)(7*sizeof(CMatrixValue)));
    glVertexAttribPointer(vNormalLoc, 3, GL_FLOAT, GL_FALSE, PRIMITIVE3D_BUFFER_SIZE * sizeof(CMatrixValue), (void*)(10*sizeof(CMatrixValue)));

    glUniformMatrix4fv(vModelLoc, 1, GL_FALSE, (GLfloat*)node->mat->value);
    glUniformMatrix4fv(vCameraLoc, 1, GL_FALSE, (GLfloat*)game->camera->mat->value);
//    printf("#\r\n");
//    cmatrix4_show(node->mat);
    short* indices = (short*)cprimitive3d_getIndexBinary((CPrimitive3D*)node);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CIndexValue)*cprimitive3d_getIndexBinaryLength((CPrimitive3D*)node), indices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, cprimitive3d_getIndexBinaryLength((CPrimitive3D*)node), GL_UNSIGNED_SHORT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
  }


  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &indexBuffer);

  glutSwapBuffers();
  glutPostRedisplay();
//releaseCObject((CObject*)mat);
}

CGame* cgame_start(CGame* obj) {
  printf("## cgame_start\n");
  CApp* appObj = getCApp();
  CGame* gameObj = getCGame();

  capp_run(appObj);
  return obj;
}

void cgame_init(CObject *context, CObject *args) {
  printf("## cgame_init\n");
  CApp* appObj = getCApp();
  CGame* gameObj = getCGame();

  gameObj->fShaderLocation = cglutil_LoadShader(GL_FRAGMENT_SHADER, cstring_getBytes(gameObj->fShaderSrc));
  gameObj->vShaderLocation = cglutil_LoadShader(GL_VERTEX_SHADER, cstring_getBytes(gameObj->vShaderSrc));
  gameObj->program = glCreateProgram();
  glAttachShader(gameObj->program, gameObj->fShaderLocation);
  glAttachShader(gameObj->program, gameObj->vShaderLocation);
  glLinkProgram(gameObj->program);
  printf("main2\n");

}


CAppMouseEvent* cgame_getCurrentMouseEvent(CGame* obj) {
  return capp_getCurrentMouseEvent(getCApp());
}
