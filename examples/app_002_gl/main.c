#include <stdio.h>
#include "app/capp.h"
#include "core/ccore.h"


int fps;
CApp* appObj;
int frgShader;
int verShader;
int program;
void _onInit(CObject* context, CObject* args) {
  printf("onInit\r\n");
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
      "attribute vec4 a_Position;\n"
      "void main() {\n"
      "  gl_Position = a_Position;\n"
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
/*  GLfloat vertexBufferData[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f
  };

  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);


  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(
     0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
     3,                  // size
     GL_FLOAT,           // type
     GL_FALSE,           // normalized?
     0,                  // stride
     (void*)0            // array buffer offset
  );
  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
  glDisableVertexAttribArray(0);

*/
  if(fps != appObj->fps) {
    fps = appObj->fps;
    printf("fps:%d;\r\n",fps);
  }
  //capp_flushBuffers(appObj);
  //capp_postRedisplay(appObj);
}

int main(int argc, char** argv) {
  printf("capp sample");
  appObj = initCApp(newCApp(getCMemory()), 400, 300);
  CString *context = initCString(newCString(getCMemory()), "dummy");
  capp_addDisplayEventListener(appObj, (CObject*)context, _onDisplay);
  capp_addInitEventListener(appObj,  (CObject*)context, _onInit);
  capp_run(appObj);
  return 0;
}
