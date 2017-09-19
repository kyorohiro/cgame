#include <stdio.h>
#include "app/capp.h"
#include "core/ccore.h"
#include "app/cimage.h"
#include "app/cttf.h"
#include "app/cdynaTexAtlas.h"

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


CDynaTexAtlas* atlas;
CDynaBlockSpace out;
void _onInit(CObject* context, CObject* args) {
  printf("## onInit\r\n");
  CApp* appObj = (CApp*)context;

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

  atlas = createCDynaTexAtlas(512, 512);
  ctexAtlas_addImageFromCTtf(atlas, font, "Hello World!!", 0.0, 0.0, 0.0, 1.0, &out);
  printf("%d %d %d %d\r\n", out.x, out.y, out.w, out.h);

  ctexAtlas_addImageFromCTtf(atlas, font, "Hello World!!", 1.0, 1.0, 0.0, 1.0, &out);
  printf("%d %d %d %d\r\n", out.x, out.y, out.w, out.h);
/*
  CImage* img = cttf_createCImageAtSolid(font, "Hello World!!", 0.0, 0.0, 0.0, 1.0);
  int imageW = cimage_getWidth(img);
  int imageH = cimage_getHeight(img);
  ctexAtlas_addImageFromSDLSurface(atlas, img->value, &out);
  printf("%d %d %d %d\r\n", out.x, out.y, out.w, out.h);
*/
}

void _onDisplay(CObject* context, CObject* args) {
  CApp* appObj = (CApp*)context;
  //
  //
  int texture;
  GLenum data_fmt = cimage_getColorFormatGL(ctexAtlas_getImage(atlas), GL_RGB);
  void* pixels = cimage_getPixels(ctexAtlas_getImage(atlas));
  int imageW = 512;//out.w;
  int imageH = 512;//out.h;

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
  //
  //releaseCObject((CObject*)img);
  //

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
  CApp* appObj = createCApp(512, 512);
  capp_addDisplayEventListener(appObj, (CObject*)appObj, _onDisplay);
  capp_addInitEventListener(appObj,  (CObject*)appObj, _onInit);
  capp_run(appObj);
  return 0;
}
