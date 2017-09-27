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
//#include <GL/gl.h>
//#include <GL/glut.h>
#endif

//
//
//
#ifdef PLATFORM_MINGW
#include <glew.h>
#if defined(GLEW_EGL)
#include <eglew.h>
#elif defined(GLEW_OSMESA)
#define GLAPI extern
#include <osmesa.h>
#elif defined(_WIN32)
#include <wglew.h>
#elif !defined(__APPLE__) && !defined(__HAIKU__) || defined(GLEW_APPLE_GLX)
#include <glxew.h>
#endif
#else
#include <SDL_opengl.h>
#endif

GLuint cglu_loadShader(GLenum type, const char *shaderSrc);

#endif
