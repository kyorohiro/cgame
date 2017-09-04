#ifdef GL_ES
precision mediump float;
#endif

attribute vec3 position;
attribute vec4 color;
attribute vec3 normal;
uniform mat4 model;
uniform mat4 camera;
varying vec4 vColor;
//
varying vec3 NNormal;
varying vec3 FragPos;


void main() {
  vColor = color;
  NNormal = normal;
  FragPos = vec3(vec4(position, 1.0));
  gl_Position = camera * vec4(position, 1.0);
}
