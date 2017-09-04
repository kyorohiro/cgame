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

mat3 transposeMat3(mat3 m) {
  float a00 = m[0][0];
  float a01 = m[0][1];
  float a02 = m[0][2];
  float a10 = m[1][0];
  float a11 = m[1][1];
  float a12 = m[1][2];
  float a20 = m[2][0];
  float a21 = m[2][1];
  float a22 = m[2][2];

  return mat3(a00, a10, a20,
             a01, a11, a21,
             a02, a12, a22);
}

mat3 inverseMat3(mat3 m) {
  float a00 = m[0][0];
  float a01 = m[0][1];
  float a02 = m[0][2];
  float a10 = m[1][0];
  float a11 = m[1][1];
  float a12 = m[1][2];
  float a20 = m[2][0];
  float a21 = m[2][1];
  float a22 = m[2][2];
  float b01 = a22 * a11 - a12 * a21;
  float b11 = -a22 * a10 + a12 * a20;
  float b21 = a21 * a10 - a11 * a20;
  float det = a00 * b01 + a01 * b11 + a02 * b21;
  return mat3(b01/det, (-a22 * a01 + a02 * a21)/det, (a12 * a01 - a02 * a11)/det,
              b11/det, (a22 * a00 - a02 * a20)/det, (-a12 * a00 + a02 * a10)/det,
              b21/det, (-a21 * a00 + a01 * a20)/det, (a11 * a00 - a01 * a10)/det);
}

void main() {
  vColor = color;
  vec4 t = model * vec4(normal, 1.0);
  mat3 xx = mat3(model[0].xyz, model[1].xyz, model[2].xyz);//mat3(mm);
  xx = inverseMat3(transposeMat3(xx));
  NNormal = normalize(xx * normal);
  FragPos = vec3(model * vec4(position, 1.0));
  gl_Position = camera * model * vec4(position, 1.0);

}
