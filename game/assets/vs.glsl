#ifdef GL_ES
precision mediump float;
#endif

attribute vec3 position;
attribute vec4 color;
attribute vec3 rot;
attribute vec3 normal;
uniform mat4 model;
uniform mat4 camera;
varying vec4 vColor;
//
varying vec3 Normal;
varying vec3 FragPos;
void main() {
  vColor = color;
  mat4 rotX = mat4(
    1.0        , 0.0         , 0.0         , 0.0,
    0.0        , cos(rot[0]) , sin(rot[0]) , 0.0,
    0.0        , -sin(rot[0]), cos(rot[0]) , 0.0,
    0.0        , 0.0         , 0.0         , 1.0
  );
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
  mat4 mm = rotY * rotZ;
  mm = rotX * mm;
  mm = camera * model * mm;

  gl_Position = mm * vec4(position, 1.0);

  FragPos = vec3(model * vec4(position, 1.0));
  Normal = normal;
}
