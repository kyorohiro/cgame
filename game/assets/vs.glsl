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
varying vec3 NNormal;
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
  mat4 mm = rotY * rotZ * rotX;
  mm = model;// * mm;
  vec4 t = mm * vec4(normal, 1.0);

  mat4 xx = mat4(
    mm[0].x, mm[1].x, mm[2].x, 0.0,
    mm[0].y, mm[1].y, mm[2].y, 0.0,
    mm[0].z, mm[1].z, mm[2].z, 0.0,
    0.0, 0.0, 0.0, 1.0
  );
//  NNormal = vec3( xx * vec4(0.0, 0.0, 1.0, 1.0));
//  NNormal = -1.0*vec3(0.0, 0.0, -1.0);
  NNormal = vec3(xx * normalize(vec4(normal, 1.0)));
  FragPos = vec3(mm * vec4(position, 1.0));
  gl_Position = camera * mm * vec4(position, 1.0);


}
