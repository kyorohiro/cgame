#include <stdio.h>
#include "app/capp.h"
#include "core/ccore.h"
#include "app/cimage.h"
#include "app/cttf.h"

int fps;
int frgShader;
int verShader;
int program;

GLfloat vertexBufferData[] = {
  0.5f, 0.5f, 0.0f,    1.0, 0.0,
  0.5f, -0.5f, 0.0f,   1.0, 1.0,
  -0.5f, -0.5f, 0.0f,  0.0, 1.0,
  -0.5f, 0.5f, 0.0f,   0.0, 0.0
};

GLshort indexData[] = {
  0,3,1, 2,1,3
};

CImage* img;
CImage* tex;
void _onInit(CObject* context, CObject* args) {
  CApp* appObj = (CApp*)context;
  printf("## onInit\r\n");
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, appObj->width, appObj->height);
  glClearColor(1.0, 0.7, 0.7, 1.0);//rgba
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  //

  CTry {
    frgShader = cglu_loadShader(GL_FRAGMENT_SHADER,
      "#ifdef GL_ES\n"
      "precision mediump float;\n"
      "#endif\n"
      "uniform sampler2D texture;\n"
      "varying vec2 textureCoord;\n"
      "void main() {\n"
      "  gl_FragColor = texture2D(texture, textureCoord)* vec4(0.9, 0.9, 0.9, 0.9) + vec4(0.1,0.1,0.1,0.1);\n"
      "}\n");
    verShader = cglu_loadShader(GL_VERTEX_SHADER,
      "attribute vec4 position;\n"
      "attribute vec2 texCoord;\n"
      "varying vec2 textureCoord;\n"
      "void main() {\n"
      "  textureCoord = texCoord;\n"
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

  //
  CTtfMgr* mgr = getCTtfMgr();
  CTtf* font = cttfMgr_createTtf(mgr, "./examples/assets/Roboto-Bold.ttf", 60);

  tex = createEmptyRPGACImage(512, 512);
  char* buff = cimage_getPixels(tex);
  for(int i=0;i<512*512;i++) {
    buff[4*i+0] = 0x00;
    buff[4*i+1] = 0x00;
    buff[4*i+2] = 0x00;
    buff[4*i+3] = 0x00;
  }
  img = cttf_createCImageAtSolid(font, "Hello World!!", 0.0, 0.0, 0.0, 1.0);
  int imageW = cimage_getWidth(img);
  int imageH = cimage_getHeight(img);
  cimage_update(tex, 0, 0, imageW, imageH, img, 0, 0, imageW, imageH);
  printf("\r\n");
}

void _onDisplay(CObject* context, CObject* args) {
  CApp* appObj = (CApp*)context;
  //
  //
  int texture;
  GLenum data_fmt = cimage_getColorFormatGL(tex, GL_RGB);
  void* pixels = cimage_getPixels(tex);
  int imageW = cimage_getWidth(tex);
  int imageH = cimage_getHeight(tex);

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // buffer
  GLuint vertexBuffer;
  GLuint indexBuffer;
  GLuint textureBuffer;
  glGenBuffers(1, &vertexBuffer);
  glGenBuffers(1, &indexBuffer);
  glGenTextures(1,&textureBuffer);

  glBindTexture(GL_TEXTURE_2D, textureBuffer);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, data_fmt,//GL_RGBA,//data_fmt,
      imageW, imageH, 0, data_fmt, GL_UNSIGNED_BYTE, pixels);
  glGenerateMipmap(GL_TEXTURE_2D);

  //
  // shader
  glUseProgram(program);
  int positionLoc = glGetAttribLocation(program, "position");
  int texCoordLoc = glGetAttribLocation(program, "texCoord");
  glEnableVertexAttribArray(positionLoc);
  glEnableVertexAttribArray(texCoordLoc);


  //
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*5*4, vertexBufferData, GL_STATIC_DRAW);

  glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
  glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3* sizeof(GLfloat)));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLshort)*6, indexData, GL_STATIC_DRAW);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

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
  CApp* appObj = createCApp(300, 300);
  capp_addDisplayEventListener(appObj, (CObject*)appObj, _onDisplay);
  capp_addInitEventListener(appObj,  (CObject*)appObj, _onInit);
  capp_run(appObj);
  return 0;
}
