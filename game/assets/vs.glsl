attribute vec3 vPosition;
attribute vec4 color;
varying vec4 vColor;

void main() {
  vColor = color;
  gl_Position = vec4(vPosition, 1.0);
}
