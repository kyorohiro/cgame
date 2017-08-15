#ifndef _H_CAPP
#define _H_CAPP

#include "core/cobject.h"
#include "core/cmemory.h"
#include "core/cstring.h"
//
//
//

#ifndef _H_LOADSHADER_
#define _H_LOADSHADER_
//
//
//
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

GLuint cglutil_LoadShader(GLenum type, const char *shaderSrc);

#endif

//
//

#define CAPP_NAME "cap"

typedef struct {
  CObject parent;
  char title[256];
  int width;
  int height;
} CApp;

//
// unused CGame is singleton
//
CApp* newCApp(CMemory* mem);
CApp* initCApp(CApp*);
CApp* getCApp();
CApp* capp_start(CApp*);
#endif