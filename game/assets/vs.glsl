attribute vec3 position;
attribute vec4 color;
attribute vec3 rot;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec4 vColor;


void main() {
  vColor = color;
  mat4 rotX = mat4(
    1.0, 0.0, 0.0,0.0,
    0.0, cos(rot[0]),sin(rot[0]),0.0,
    0.0, -sin(rot[0]),cos(rot[0]),0.0,
    0.0, 0.0,0.0,1.0
  );
  gl_Position = projection * view * rotX * vec4(position, 1.0);
}
