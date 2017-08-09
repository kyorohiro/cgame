#include "cgame.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/cbytesBuilder.h"

#include "cglutil.h"
#include "cprimitive3d.h"
//
void cgame_draw(void);

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
  obj->root = initCObject3D(newCObject3D(obj->parent.cmemory));
//  obj->fShaderLocation = cglutil_LoadShader(GL_VERTEX_SHADER, cstring_getBytes(obj->fShaderSrc));
//  obj->vShaderLocation = cglutil_LoadShader(GL_VERTEX_SHADER, cstring_getBytes(obj->vShaderSrc));
  //
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

void cgame_draw(void) {
  CGame *game = getCGame();
  CObject3D *root = (CObject3D*)cgame_getRoot(game);
  cobject3d_enterFrame(root, (CObject*)game);
  //
  CLinkedList *nodes = cobject3d_getNodes(root);

  glClear(GL_COLOR_BUFFER_BIT);




  int vProjectionLoc = glGetUniformLocation(game->program, "projection");
  int vViewLoc = glGetUniformLocation(game->program, "view");
  int vModelLoc = glGetUniformLocation(game->program, "model");

  //
  //
  CMatrix4 mat2;
  cmatrix4_setIdentity(initCMatrix4(&mat2));
  CMatrix4 mat;
  cmatrix4_setIdentity(initCMatrix4(&mat));

//  cmatrix4_setLookAt(&mat2,
//    0.0, -1.0, -1.0,
//    0.0, 0.0, 0.0,
//    0.0, 0.0, 0.0);
//cmatrix4_setRotationX(&mat2, 3.14*20.0/180.0);
  //cmatrix4_setPerspectiveProjection(&mat, 2.0, -2.0, 2.0, -2.0, -2.0,10.0);
  cmatrix4_setOrthogonalProjection(&mat2, 2.0, -2.0, 2.0, -2.0, 0.1 , 1000.0);
  glUniformMatrix4fv(vProjectionLoc, 1, GL_FALSE, mat.value);
  glUniformMatrix4fv(vViewLoc, 1, GL_FALSE, mat.value);
  glUniformMatrix4fv(vModelLoc, 1, GL_FALSE, mat.value);
  glUniformMatrix4fv(vViewLoc, 1, GL_FALSE, (GLfloat*)mat.value);
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
    glEnableVertexAttribArray(vPositionLoc);
    glEnableVertexAttribArray(vColorLoc);
    glEnableVertexAttribArray(vRotLoc);

    glVertexAttribPointer(vPositionLoc, 3, GL_FLOAT, GL_FALSE, 10*sizeof(CMatrixValue), (void*)0);
    glVertexAttribPointer(vColorLoc, 4, GL_FLOAT, GL_FALSE, 10*sizeof(CMatrixValue), (void*)(3*sizeof(CMatrixValue)));
    glVertexAttribPointer(vRotLoc, 3, GL_FLOAT, GL_FALSE, 10*sizeof(CMatrixValue), (void*)(7*sizeof(CMatrixValue)));
    glUniformMatrix4fv(vModelLoc, 1, GL_FALSE, (GLfloat*)node->mat->value);
    glUniformMatrix4fv(vViewLoc, 1, GL_FALSE, (GLfloat*)mat2.value);
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
  printf("main\n");
  CGame* gameObj = getCGame();

  char *argv = "test";
  glutInit(0, &argv);
  glutInitWindowSize(gameObj->width, gameObj->height);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutCreateWindow("es2gears");
  glClearColor(0.9f, 1.0f, 0.9f, 1.0f);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  //
  //
  obj->fShaderLocation = cglutil_LoadShader(GL_FRAGMENT_SHADER, cstring_getBytes(obj->fShaderSrc));
  obj->vShaderLocation = cglutil_LoadShader(GL_VERTEX_SHADER, cstring_getBytes(obj->vShaderSrc));
  obj->program = glCreateProgram();
  glAttachShader(obj->program, obj->fShaderLocation);
  glAttachShader(obj->program, obj->vShaderLocation);
//  glBindAttribLocation(obj->program, 0, "vPosition");
  glLinkProgram(obj->program);
//  int vPositionLocation = glGetAttribLocation(obj->program, "vPosition");

  //glutIdleFunc (gears_idle);
  //glutReshapeFunc(gears_reshape);
  glutDisplayFunc(cgame_draw);
  //glutSpecialFunc(gears_special);
  //glutMouseFunc(mouseCB);

  glUseProgram(obj->program);
  //
  //
  glutMainLoop();
  return obj;
}
