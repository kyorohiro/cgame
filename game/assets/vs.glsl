#ifdef GL_ES
precision mediump float;
#endif

attribute vec3 position;
attribute vec4 color;
attribute vec3 rot;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec4 vColor;

void main() {
//  vColor = colorr * color;
  vColor = color;

  float rz = rot[2];
  mat4 rotZ = mat4(
     cos(rz) , sin(rz), 0.0         , 0.0,
     -sin(rz), cos(rz), 0.0         , 0.0,
     0.0         , 0.0        , 1.0         , 0.0,
    0.0         , 0.0        , 0.0         , 1.0
  );
  gl_Position = rotZ*vec4(position, 1.0);
}
