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

GLuint cglu_loadShader(GLenum type, const char *shaderSrc);

#endif
