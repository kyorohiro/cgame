#include <stdio.h>
// #include <GLES2/gl2.h>
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>
//#include <GL/gl.h>

#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES

#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <Glut/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif


#define STRIPS_PER_TOOTH 7
#define VERTICES_PER_TOOTH 34
#define GEAR_VERTEX_STRIDE 6

#include <emscripten.h>
#define MULTILINE(...) #__VA_ARGS__
int colorIndex = 0;


GLuint LoadShader(GLenum type, const char *shaderSrc);

GLuint vertexShader;
GLuint fragmentShader;
GLuint programObject;
int initGame() {
  printf("initGame\n");
  char *vShaderStr =
  "attribute vec4 vPosition; \n"
  "void main() \n"
  "{ \n"
  "  gl_Position = vPosition;\n"
  "} \n";

  char *fShaderStr =
  "precision mediump float; \n"
  "void main() \n"
  "{ \n"
  "  gl_FragColor = vec4(1.0,0.0,0.0,1.0);\n"
  "} \n";


  GLint linked;
  vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
  fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);

// Create the program object
  programObject = glCreateProgram();
  if(programObject == 0) {
    return 0;
  }

  glAttachShader(programObject, vertexShader);
  glAttachShader(programObject, fragmentShader);
  // Bind vPosition to attribute 0
  glBindAttribLocation(programObject, 0, "vPosition");
  // Link the program
  glLinkProgram(programObject);
  // Check the link status
  glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
  if(!linked) {
    GLint infoLen = 0;
    glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
    if(infoLen > 1) {
      char* infoLog = malloc(sizeof(char) * infoLen);
      glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
      printf("Error linking program:\n%s\n", infoLog);
      free(infoLog);
    }
    glDeleteProgram(programObject);
    return 0;
  }
  // Store the program object userData->programObject = programObject;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  return 1;
}

void _gears_draw(void) {
  printf("draw\n");
  double v = colorIndex/255.0;
  glClearColor(v, v, v, v);
//  glClearColor(0.5, 0.5, 0.5, 0.5);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSwapBuffers();
  colorIndex++;
  printf("s %d %f \n",colorIndex, v);

  if(colorIndex > 255) {
    colorIndex = 0;
  }
  printf("e %d\n",colorIndex);
}
void gears_draw(void) {
    printf("draw\n");
  GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f};
  // Set the viewport
  // Clear the color buffer
  glClear(GL_COLOR_BUFFER_BIT);
  // Use the program object
  glUseProgram(programObject);
  // Load the vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
  glEnableVertexAttribArray(0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glutSwapBuffers();
}

void gears_reshape(int width, int height)
{
  printf("reshape\n");
  /* Update the projection matrix */
  //perspective(ProjectionMatrix, 60.0, width / (float)height, 1.0, 1024.0);

  /* Set the viewport */
  glViewport(0, 0, (GLint) width, (GLint) height);
}

void gears_idle(void) {
//    printf("idle\n");
      glutPostRedisplay();
}

void gears_special(int special, int crap, int morecrap) {
    printf("%d %d %d\n", special, crap, morecrap );
//    glutSwapBuffers();
    glutPostRedisplay();

}

void mouseCB(int button, int state, int x, int y) {
  printf("%d %d %d %d\n", button, state, x, y);
}

int main(int argc, char *argv[])
{
    printf("main\n");
   /* Initialize the window */
   glutInit(&argc, argv);
   glutInitWindowSize(300, 300);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

   glutCreateWindow("es2gears");

   /* Set up glut callback functions */
   //glutIdleFunc (gears_idle);
   glutReshapeFunc(gears_reshape);
   glutDisplayFunc(gears_draw);
   glutSpecialFunc(gears_special);
   glutMouseFunc(mouseCB);

   /* Initialize the gears */
   //
   //
   //
   {
     printf("f00\n");
    FILE *fp = fopen("/assets/fs.glsl", "r");
    printf("f01 \n");

    int i;
    for(i=0;i<1000;i++)
    {
      printf("f02\n");

       int c = fgetc(fp);
       if( feof(fp) )
       {
          break ;
       }
       printf("%c", c);
       //break;
    }
    fclose(fp);
  }
   //gears_init();
   initGame();
   glutMainLoop();
   emscripten_run_script(MULTILINE(
       Module.injectEvent = function(eventType, wantedX, wantedY) {
           // Desktop browsers do not have the event types for touch events,
           // so we fake them by creating a plain-vanilla UIEvent and then
           // filling in the fields that we look for with appropriate values.
           var rect = Module["canvas"].getBoundingClientRect();
           Module['print']('rect corner: ' + rect.left + ',' + rect.top);
           Module['print']('wanted: ' + wantedX + ',' + wantedY);
           var x = wantedX + rect.left;
           var y = wantedY + rect.top;
           var touch = {
               identifier: 0,
               clientX: x,
               clientY: y,
               screenX: x,
               screenY: y,
               pageX: x,
               pageY: y,
               target: Module['canvas']
           };
           var touches = [ touch ];
           touches.item = function(i) { return this[i]; };

           var event = document.createEvent('UIEvent');
           event.target = Module['canvas'];
           event.button = 0;
           event.changedTouches = touches;
           event.initUIEvent(eventType, true, true, window, 1);
           Module['canvas'].dispatchEvent(event);
       }
   ));

   return 0;
}

//
//
//
GLuint LoadShader(GLenum type, const char *shaderSrc){
  GLuint shader;
  GLint compiled;
  shader = glCreateShader(type);
  if(shader == 0) {
    return 0;
  }

  glShaderSource(shader, 1, &shaderSrc, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if(!compiled) {
    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    if(infoLen > 1) {
      char* infoLog = malloc(sizeof(char) * infoLen);
      glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
      printf("Error compiling shader:\n%s\n", infoLog);
      free(infoLog);
    }
    glDeleteShader(shader);
    return 0;
  }
  return shader;
}
