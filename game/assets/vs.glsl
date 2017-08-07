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
  mat4 rotY = mat4(
    cos(rot[1]), 0.0, -sin(rot[1]), 0.0,
    0.0        , 1.0, 0.0         , 0.0,
    sin(rot[1]), 0.0, cos(rot[1]) , 0.0,
    0.0        , 0.0, 0.0         , 1.0
  );
  mat4 rotZ = mat4(
     cos(rot[2]) , sin(rot[2]), 0.0         , 0.0,
     -sin(rot[2]), cos(rot[2]), 0.0         , 0.0,
     0.0         , 0.0        , 1.0         , 0.0,
    0.0         , 0.0        , 0.0         , 1.0
  );
  gl_Position = rotY*rotZ*vec4(position, 1.0);
}
