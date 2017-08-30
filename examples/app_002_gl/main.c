#include <stdio.h>
#include "app/capp.h"
#include "core/ccore.h"


int fps;
CApp* appObj;
int frgShader;
int verShader;
int program;

GLfloat vertexBufferData[] = {
  0.0f, 0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f
};

GLshort indexData[] = {
  0,1,2
};

void _onInit(CObject* context, CObject* args) {
  printf("## onInit\r\n");

  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, appObj->width, appObj->height);
  glClearColor(1.0, 0.7, 0.7, 1.0);//rgba
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  //

  CTry {
    frgShader = cglu_loadShader(GL_FRAGMENT_SHADER,
      "void main() {\n"
      "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
      "}\n");
    verShader = cglu_loadShader(GL_VERTEX_SHADER,
      "attribute vec4 position;\n"
      "void main() {\n"
      "  gl_Position = position;\n"
      "}\n");
  } CCatch {
    printf("## ERROR\r\n");
    return;
  }

  program = glCreateProgram();
  glAttachShader(program, frgShader);
  glAttachShader(program, verShader);
  glLinkProgram(program);

}

void _onDisplay(CObject* context, CObject* args) {

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  GLuint vertexBuffer;
  GLuint indexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glGenBuffers(1, &indexBuffer);

  glUseProgram(program);
  int positionLoc = glGetAttribLocation(program, "position");

  //
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*3*3, vertexBufferData, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLshort)*3, indexData, GL_STATIC_DRAW);


  glEnableVertexAttribArray(positionLoc);
  glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &indexBuffer);

  if(fps != appObj->fps) {
    fps = appObj->fps;
    printf("fps:%d;\r\n",fps);
  }

  capp_flushBuffers(appObj);
  //capp_postRedisplay(appObj);
}

int main(int argc, char** argv) {
  printf("capp sample\r\n");
  //appObj = getCApp();//
  appObj = initCApp(newCApp(getCMemory()), 400, 300);
  CString *context = initCString(newCString(getCMemory()), "dummy");
  capp_addDisplayEventListener(appObj, (CObject*)context, _onDisplay);
  capp_addInitEventListener(appObj,  (CObject*)context, _onInit);
  capp_run(appObj);
  return 0;
}
