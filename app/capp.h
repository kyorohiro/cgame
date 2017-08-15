#ifndef _H_CAPP
#define _H_CAPP

#include "core/cobject.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/cevent.h"
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
#define CAPP_EVENT_MOUSE "cmo"

typedef struct {
  CObject parent;
  int state;
  double x;
  double y;
} CAppMouseEvent;

typedef struct {
  CObject parent;
  char title[256];
  int width;
  int height;
  CAppMouseEvent *mouseEvent;
  CEventDispatcher *mouse;
  CEventDispatcher *display;
} CApp;

//
// unused CGame is singleton
//
CApp* newCApp(CMemory* mem);
CApp* initCApp(CApp*);
CApp* getCApp();
CApp* capp_start(CApp*);

CApp* capp_addMouseEventListener(CApp*, CObject* context, CEventFuncOnEvent func);
CApp* capp_addDisplayEventListener(CApp*, CObject* context, CEventFuncOnEvent func);

//
// Mouse Event
//
CAppMouseEvent* newCAppMouseEvent(CMemory* mem);
CAppMouseEvent* initCAppMouseEvent(CAppMouseEvent*, int state, float x, float y);
#endif
