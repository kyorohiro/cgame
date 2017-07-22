#include "cgame.h"
#include "core/cmemory.h"

#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES

#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <Glut/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

void cgame_draw(void);

CGame* newCGame(CMemory* mem) {
  CGame * ret = cmemory_calloc(mem, 1, sizeof(CGame));
  ret->parent.cmemory = mem;
  return ret;
}

CGame* initCGame(CGame* obj) {
  initCObject((CObject*)obj, OBJECT3D_NAME);
  snprintf(obj->title, sizeof(obj->title), "%s", "title");
  obj->width = 400;
  obj->height = 300;
  return obj;
}

CGame* defaultCGame = NULL;
CGame* getCGame() {
  if(defaultCGame == NULL) {
    defaultCGame = initCGame(newCGame(getCMemory()), "cgame_default");
    FILE *fp = fopen("/game/assets/vs.glsl","r");
    while(1)
    {
     int c = fgetc(fp);
     if( feof(fp) )
     {
        break ;
     }
     printf("%c", c);
    }
    fclose(fp);
  }
  return defaultCGame;
}

void cgame_draw(void) {
  GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f};
  // Set the viewport
  // Clear the color buffer
  glClear(GL_COLOR_BUFFER_BIT);
  // Use the program object
  //glUseProgram(programObject);
  // Load the vertex data
  //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
  //glEnableVertexAttribArray(0);
  //glDrawArrays(GL_TRIANGLES, 0, 3);
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
  //glutIdleFunc (gears_idle);
  //glutReshapeFunc(gears_reshape);
  glutDisplayFunc(cgame_draw);
  //glutSpecialFunc(gears_special);
  //glutMouseFunc(mouseCB);
  glutMainLoop();
  return obj;
}
