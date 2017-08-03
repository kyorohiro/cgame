#include "cgame.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/cbytesBuilder.h"

#include "cglutil.h"
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
//  obj->fShaderLocation = cglutil_LoadShader(GL_VERTEX_SHADER, cstring_getBytes(obj->fShaderSrc));
//  obj->vShaderLocation = cglutil_LoadShader(GL_VERTEX_SHADER, cstring_getBytes(obj->vShaderSrc));
  //

  return obj;
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
  GLfloat vVertices[] = {
    0.0f, 0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f};
  // Set the viewport
  // Clear the color buffer
  glClear(GL_COLOR_BUFFER_BIT);
  // Use the program object
  glUseProgram(game->program);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
  glEnableVertexAttribArray(0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  // Load the vertex data
  glutSwapBuffers();
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
  glBindAttribLocation(obj->program, 0, "vPosition");
  glLinkProgram(obj->program);
  int vPositionLocation = glGetAttribLocation(obj->program, "vPosition");

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
