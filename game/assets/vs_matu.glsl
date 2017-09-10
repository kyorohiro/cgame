#ifdef GL_ES
precision mediump float;
#endif

uniform mat4 model;
uniform mat4 camera;

attribute vec3 position;
attribute vec4 color;
attribute vec3 normal;
attribute vec2 texCoord;

varying vec4 vColor;
varying vec3 vNormal;
varying vec3 vPosition;
varying vec2 vTexCoord;

void main() {
  vColor = color;
  vNormal = normal;
  vPosition = vec3(vec4(position, 1.0));
  vTexCoord = texCoord;
  gl_Position = camera * vec4(position, 1.0);

}
