#ifndef _H_CAPP2
#define _H_CAPP2

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
#include <SDL_events.h>
#include <SDL_opengl.h>

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
  CEventDispatcher *init;
  CEventDispatcher *mouse;
  CEventDispatcher *display;
  int debugCount;
  double debugTime;
  int fps;
} CApp;

//
// unused CGame is singleton
//
CApp* newCApp(CMemory* mem);
CApp* initCApp(CApp*);
CApp* getCApp();
CApp* capp_run(CApp*);

CApp* capp_addMouseEventListener(CApp*, CObject* context, CEventFuncOnEvent func);
CApp* capp_addDisplayEventListener(CApp*, CObject* context, CEventFuncOnEvent func);
CApp* capp_addInitEventListener(CApp*, CObject* context, CEventFuncOnEvent func);
CAppMouseEvent* capp_getCurrentMouseEvent(CApp*);
CApp* capp_postRedisplay(CApp*);
CApp* capp_flushBuffers(CApp*);
//  glutSwapBuffers();
//  glutPostRedisplay();

double capp_currentMilliSecound(CApp*);

//
// Mouse Event
//
CAppMouseEvent* newCAppMouseEvent(CMemory* mem);
CAppMouseEvent* initCAppMouseEvent(CAppMouseEvent*, int state, float x, float y);
#endif
