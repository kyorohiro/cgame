#include "cgame.h"
#include "ccamera3d.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/cbytesBuilder.h"

#include "cglutil.h"
#include "cprimitive3d.h"
#include "croot3d.h"
#include "app/capp.h"

void cgame_draw_ume(CObject *context, CObject *args) {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  CGame *game = getCGame();
  CObject3D *root = (CObject3D*)cgame_getRoot(game);
  if(root == NULL) {
    printf("ROOT == NULL\r\n");
    return;
  }
  //
  CLinkedList *nodes = cobject3d_getNodes(root);
  glClear(GL_COLOR_BUFFER_BIT);
  if(nodes == NULL) {
    printf("NODES == NULL\r\n");
    return;
  }

  cobject3d_enterFrame(root, root, args);

  //
  // create Buffer
  GLfloat *ver = (GLfloat *)game->vertexes->value;
  GLshort *ind = (GLshort *)game->indexes->value;


  GLuint vertexBuffer;
  GLuint indexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glGenBuffers(2, &indexBuffer);


  for(int i=0;i<clinkedList_getLength(nodes);i++) {
    CObject3D *node = (CObject3D*)clinkedList_get(nodes, i);
    if(node->type != CObject3DTypePrimitive) {
      continue;
    }
    //
    GLfloat *vVertices = (GLfloat *)cprimitive3d_getVertexBinary((CPrimitive3D *)node);
    GLfloat *vColors = (GLfloat *)cprimitive3d_getColorBinary((CPrimitive3D *)node);
    GLfloat *vNormals = (GLfloat *)cprimitive3d_getNormalBinary((CPrimitive3D *)node);
    int lens = cprimitive3d_getVertexBinaryLength((CPrimitive3D *)node) / sizeof(CMatrixVertexType);

    //
    int pointer = 0;
    int pointerI = 0;
    CVector4Raw out;
    for(int j=0;j<lens/3;j+=1) {
      ver[pointer++] =  vVertices[j*3+0];
      ver[pointer++] =  vVertices[j*3+1];
      ver[pointer++] =  vVertices[j*3+2];
      //
      ver[pointer++] =  vColors[j*4+0];
      ver[pointer++] =  vColors[j*4+1];
      ver[pointer++] =  vColors[j*4+2];
      ver[pointer++] =  vColors[j*4+3];
      //
      ver[pointer++] =  vNormals[j*3+0];
      ver[pointer++] =  vNormals[j*3+1];
      ver[pointer++] =  vNormals[j*3+2];
      //
    }

    int len = cprimitive3d_getIndexBinaryLength((CPrimitive3D*)node) / sizeof(CMatrixIndexType);
    GLshort *indices = (GLshort *)cprimitive3d_getIndexBinary((CPrimitive3D*)node);
    for(int j=0;j<len;j++) {
      ind[pointerI++] =  indices[j];
    }
    //
    //
    //
    glUseProgram(game->program);
    int vPositionLoc = glGetAttribLocation(game->program, "position");
    int vColorLoc    = glGetAttribLocation(game->program, "color");
    int vNormalLoc    = glGetAttribLocation(game->program, "normal");
    int vCameraLoc = glGetUniformLocation(game->program, "camera");
    int vModelLoc = glGetUniformLocation(game->program, "model");
    glEnableVertexAttribArray(vPositionLoc);
    glEnableVertexAttribArray(vColorLoc);
    glEnableVertexAttribArray(vNormalLoc);


    int buffeSize = 10* sizeof(CMatrixVertexType);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CMatrixVertexType)*pointer, ver, GL_STATIC_DRAW);

    //  int buffeSize = PRIMITIVE3D_BUFFER_SIZE;
    glVertexAttribPointer(vPositionLoc, 3, GL_FLOAT, GL_FALSE, buffeSize, (void*)0);
    glVertexAttribPointer(vColorLoc, 4, GL_FLOAT, GL_FALSE, buffeSize, (void*)(3*sizeof(CMatrixVertexType)));
    glVertexAttribPointer(vNormalLoc, 3, GL_FLOAT, GL_FALSE, buffeSize, (void*)(7*sizeof(CMatrixVertexType)));

    glUniformMatrix4fv(vModelLoc, 1, GL_FALSE, (GLfloat*)cobject3d_getCMatrix4((CObject3D*)node)->value);
    glUniformMatrix4fv(vCameraLoc, 1, GL_FALSE, (GLfloat*)game->camera->mat->value);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pointerI*sizeof(GLshort), ind, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, pointerI, GL_UNSIGNED_SHORT, 0);

  }

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(2, &indexBuffer);

  capp_flushBuffers(game->app);

}
