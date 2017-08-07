attribute vec3 position;
attribute vec4 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec4 vColor;


void main() {
  vColor = color;
  mat4 rotX = mat4(
    1.0, 0.0, 0.0,0.0,
    0.0, cos(0.52*2.0),sin(0.52*2.0),0.0,
    0.0, -sin(0.52*2.0),cos(0.52*2.0),0.0,
    0.0, 0.0,0.0,1.0
  );
  gl_Position = projection * view * rotX * vec4(position, 1.0);
}
