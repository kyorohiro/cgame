#ifdef GL_ES
precision mediump float;
#endif

attribute vec3 position;
attribute vec4 color;
attribute vec3 rot;
uniform mat4 model;
uniform mat4 camera;
varying vec4 vColor;

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
  //

  vec3 ambientLight = vec3(0.6, 0.6, 0.6);
  vec3 directionalLightColor = vec3(0.5, 0.5, 0.75);
  vec3 directionalVector = vec3(0.85, 0.8, 0.75);

  //vec4 transformedNormal = model * vec4(position, 1.0);
  //float directional = max(dot(transformedNormal.xyz, directionalVector), 0.0);
  gl_Position = mm * vec4(position, 1.0);
}
