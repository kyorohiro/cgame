#include "cgame.h"
#include "ccamera3d.h"
#include "core/cmemory.h"
#include "core/cstring.h"
#include "core/cbytesBuilder.h"

#include "app/cglu.h"
#include "cprimitive3d.h"
#include "croot3d.h"
#include "app/capp.h"

//
//int max_attribs;
//glGetIntegerv (GL_MAX_VERTEX_ATTRIBS, &max_attribs);
//printf(">>%d");
//
void cgame_draw_matu(CObject *context, CObject *args) {
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

 CGame *game = getCGame();
 CObject3D *root = (CObject3D*)cgame_getRoot(game);
 if(root == NULL) {
   printf("ROOT == NULL\r\n");
   return;
 }

 CLinkedList *nodes = cobject3d_getNodes(root);
 glClear(GL_COLOR_BUFFER_BIT);
 if(nodes == NULL) {
   printf("NODES == NULL\r\n");
   return;
 }

 //
 // event loop
 cobject3d_enterFrame(root, root, args);



 CMatrix4Raw modelMat;
 cmatrix4raw_setIdentity(modelMat);

 //game->vertexes
 GLfloat *ver = (GLfloat *)game->vertexes->value;
 GLshort *ind = (GLshort *)game->indexes->value;
 int pointer = 0;
 int pointerI = 0;
 CImage *texture = NULL;
   int pBase = 0;
 for(int i=0;i<clinkedList_getLength(nodes);i++) {
   CObject3D *node = (CObject3D*)clinkedList_get(nodes, i);
   if(node->type != CObject3DTypePrimitive) {
     continue;
   }
   GLfloat *vVertices = (GLfloat *)cprimitive3d_getVertexBinary((CPrimitive3D *)node);
   GLfloat *vColors = (GLfloat *)cprimitive3d_getColorBinary((CPrimitive3D *)node);
   GLfloat *vNormals = (GLfloat *)cprimitive3d_getNormalBinary((CPrimitive3D *)node);
   CImage *image = texture = cprimitive3d_getCImage((CPrimitive3D *)node);
   GLfloat *texCoords = (GLfloat*)cprimitive3d_getTextCoordBinary((CPrimitive3D*)node);

   CMatrix4RawRef mat4 = cobject3d_getCMatrix4((CObject3D *)node)->value;
   int len = cprimitive3d_getVertexBinaryLength((CPrimitive3D *)node) / sizeof(CMatrixVertexType);
   CMatrix4RawRef m = cobject3d_getCMatrix4((CObject3D *)node)->value;

   CMatrix4Raw n;
   CVMFloat outDeterminant;
   cmatrix4raw_transpose(m, n);
   cmatrix4raw_inverse(n, n, &outDeterminant);



   CVector4Raw out;
   for(int j=0;j<len/3;j+=1) {
     cmatrix4raw_mulVector(m, vVertices[j*3+0], vVertices[j*3+1], vVertices[j*3+2], 1.0, out);
     ver[pointer++] =  out[0];
     ver[pointer++] =  out[1];
     ver[pointer++] =  out[2];
     //printf("[%d] %f %f %f \r\n ", j, out[0], out[1], out[2]);
     ver[pointer++] =  vColors[j*4+0];
     ver[pointer++] =  vColors[j*4+1];
     ver[pointer++] =  vColors[j*4+2];
     ver[pointer++] =  vColors[j*4+3];
     //
     // mul(normal(inverseMat3(transposeMat3(model))), normal)
     cmatrix4raw_mulVector(n, vNormals[j*3+0], vNormals[j*3+1], vNormals[j*3+2], 1.0, out);
     cvector4raw_normalize(out, out);
     ver[pointer++] =  out[0];
     ver[pointer++] =  out[1];
     ver[pointer++] =  out[2];

     //
     if(image == NULL) {
       ver[pointer++] =  -1.0;
       ver[pointer++] =  -1.0;
     } else {
//       ver[pointer++] =  -1.0;
//       ver[pointer++] =  -1.0;
       ver[pointer++] =  texCoords[j*2+0];
       ver[pointer++] =  texCoords[j*2+1];
     }

   }
  // printf("\r\n\r\n ##");
   //
   GLshort *indices = (GLshort *)cprimitive3d_getIndexBinary((CPrimitive3D*)node);
   len = cprimitive3d_getIndexBinaryLength((CPrimitive3D*)node)  / sizeof(CMatrixIndexType);

   //printf(">> %d\r\n", pBase);
   for(int j=0;j<len;j++) {
     ind[pointerI++] =  indices[j]+pBase;
   }
   pBase = pointer/12;
   //break;
 }
 /*
 printf("\r\n");
 for(int i=0;i<pointer/12;i++) {
   printf("(%f,%f,%f) ", ver[i*12+0], ver[i*12+1], ver[i*12+2]);
 }
 printf("\r\n");
 printf("\r\n");
 for(int i=0;i<pointerI;i++) {
   printf("%d ,", (int)ind[i]);
 }
 printf("\r\n");*/

 //printf("%d, %d \r\n",pointer, pointerI);
 //
 //
 //
 // create Buffer
 GLuint vertexBuffer;
 GLuint indexBuffer;
 GLuint textureBuffer;
 glGenBuffers(1, &vertexBuffer);
 glGenBuffers(2, &indexBuffer);
 if(texture != NULL) {
   glGenTextures(1,&textureBuffer);
 }

 //
 if(texture != NULL) {
  GLenum data_fmt = cimage_getColorFormatGL(texture, GL_RGB);
  void* pixels = cimage_getPixels(texture);
  int imageW = cimage_getWidth(texture);
  int imageH = cimage_getHeight(texture);
  glBindTexture(GL_TEXTURE_2D, textureBuffer);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, data_fmt,//GL_RGBA,//data_fmt,
     imageW, imageH, 0, data_fmt, GL_UNSIGNED_BYTE, pixels);
  //glGenerateMipmap(GL_TEXTURE_2D);
}
 //
 //
 glUseProgram(game->program);
 int vPositionLoc = glGetAttribLocation(game->program, "position");
 int vColorLoc    = glGetAttribLocation(game->program, "color");
 int vNormalLoc    = glGetAttribLocation(game->program, "normal");
 int vCameraLoc = glGetUniformLocation(game->program, "camera");
 int vModelLoc = glGetUniformLocation(game->program, "model");
 int vTexCoordLoc = glGetAttribLocation(game->program, "texCoord");
 glEnableVertexAttribArray(vPositionLoc);
 glEnableVertexAttribArray(vColorLoc);
 glEnableVertexAttribArray(vNormalLoc);
 glEnableVertexAttribArray(vTexCoordLoc);

 int buffeSize = (10+2)* sizeof(CMatrixVertexType);

 glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
 glBufferData(GL_ARRAY_BUFFER, sizeof(CMatrixVertexType)*pointer, ver, GL_STATIC_DRAW);

//  int buffeSize = PRIMITIVE3D_BUFFER_SIZE;
 glVertexAttribPointer(vPositionLoc, 3, GL_FLOAT, GL_FALSE, buffeSize, (void*)0);
 glVertexAttribPointer(vColorLoc, 4, GL_FLOAT, GL_FALSE, buffeSize, (void*)(3*sizeof(CMatrixVertexType)));
 glVertexAttribPointer(vNormalLoc, 3, GL_FLOAT, GL_FALSE, buffeSize, (void*)(7*sizeof(CMatrixVertexType)));
 glVertexAttribPointer(vTexCoordLoc, 2, GL_FLOAT, GL_FALSE, buffeSize, (void*)(10*sizeof(CMatrixVertexType)));

 glUniformMatrix4fv(vModelLoc, 1, GL_FALSE, (GLfloat*)modelMat);
 glUniformMatrix4fv(vCameraLoc, 1, GL_FALSE, (GLfloat*)game->camera->mat->value);

 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, pointerI*sizeof(GLshort), ind, GL_STATIC_DRAW);

 glDrawElements(GL_TRIANGLES, pointerI, GL_UNSIGNED_SHORT, 0);
// printf("%d %d\r\n", pointerI,pointer);

 glDeleteBuffers(1, &vertexBuffer);
 glDeleteBuffers(2, &indexBuffer);
 if(texture != NULL) {
  glDeleteTextures(1, &textureBuffer);
 }
 capp_flushBuffers(game->app);
}
