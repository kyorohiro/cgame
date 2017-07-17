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

CGame* newCGame(CMemory* mem) {
  CGame * ret = cmemory_calloc(mem, 1, sizeof(CGame));
  ret->parent.cmemory = mem;
  return ret;
}

CGame* initCGame(CGame* obj, char* name, char *title, int width, int height) {
  initCObject((CObject*)obj, name);
  snprintf(obj->title, sizeof(obj->title), "%s", title);
  obj->width = width;
  obj->height = height;
  return obj;
}

void gears_draw(void) {
    printf("draw\n");
  GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f};
  // Set the viewport
  // Clear the color buffer
  glClear(GL_COLOR_BUFFER_BIT);
  // Use the program object
  //glUseProgram(programObject);
  // Load the vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
  glEnableVertexAttribArray(0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glutSwapBuffers();
}

CGame* cgame_start(CGame* obj) {
  printf("main\n");
  char *argv = "test";
  glutInit(0, &argv);
  glutInitWindowSize(300, 300);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutCreateWindow("es2gears");
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  //glutIdleFunc (gears_idle);
  //glutReshapeFunc(gears_reshape);
  glutDisplayFunc(gears_draw);
  //glutSpecialFunc(gears_special);
  //glutMouseFunc(mouseCB);
  glutMainLoop();
  return obj;
}
