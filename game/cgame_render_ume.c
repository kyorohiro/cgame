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
  //
  //
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
  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);

  GLuint indexBuffer;
  glGenBuffers(1, &indexBuffer);
  for(int i=0;i<clinkedList_getLength(nodes);i++) {
    CObject3D *node = (CObject3D*)clinkedList_get(nodes, i);
    if(node->type != CObject3DTypePrimitive) {
      continue;
    }
    GLfloat *vVertices = (GLfloat *)cprimitive3d_getVertexSetBinary((CPrimitive3D *)node);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, cprimitive3d_getVertexSetBinaryLength((CPrimitive3D *)node)*10, vVertices, GL_STATIC_DRAW);
    glUseProgram(game->program);
    int vPositionLoc = glGetAttribLocation(game->program, "position");
    int vColorLoc    = glGetAttribLocation(game->program, "color");
    int vNormalLoc    = glGetAttribLocation(game->program, "normal");
    int vCameraLoc = glGetUniformLocation(game->program, "camera");
    int vModelLoc = glGetUniformLocation(game->program, "model");
    glEnableVertexAttribArray(vPositionLoc);
    glEnableVertexAttribArray(vColorLoc);
    glEnableVertexAttribArray(vNormalLoc);
    glVertexAttribPointer(vPositionLoc, 3, GL_FLOAT, GL_FALSE, PRIMITIVE3D_BUFFER_SIZE * sizeof(CMatrixVertexType), (void*)0);
    glVertexAttribPointer(vColorLoc, 4, GL_FLOAT, GL_FALSE, PRIMITIVE3D_BUFFER_SIZE * sizeof(CMatrixVertexType), (void*)(3*sizeof(CMatrixVertexType)));
    glVertexAttribPointer(vNormalLoc, 3, GL_FLOAT, GL_FALSE, PRIMITIVE3D_BUFFER_SIZE * sizeof(CMatrixVertexType), (void*)(7*sizeof(CMatrixVertexType)));

    glUniformMatrix4fv(vModelLoc, 1, GL_FALSE, (GLfloat*)node->mat->value);
    glUniformMatrix4fv(vCameraLoc, 1, GL_FALSE, (GLfloat*)game->camera->mat->value);

    short* indices = (short*)cprimitive3d_getIndexBinary((CPrimitive3D*)node);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cprimitive3d_getIndexBinaryLength((CPrimitive3D*)node), indices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, cprimitive3d_getIndexBinaryLength((CPrimitive3D*)node)/sizeof(CMatrixIndexType), GL_UNSIGNED_SHORT, 0);
  }

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &indexBuffer);

  capp_flushBuffers(game->app);

}
