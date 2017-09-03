#ifdef GL_ES
precision mediump float;
#endif

varying vec4 vColor;
varying vec3 NNormal;
varying vec3 FragPos;



void main() {
  //
  //
  vec3 lightPos = vec3(0.0,0.0,0.0);
  vec3 lightColor = vec3(1.0,1.0,1.0);
  vec3 objectColor = vec3(vColor[0],vColor[1],vColor[2]);

  float ambientStrength = 0.8;
  vec3 ambient = ambientStrength * lightColor;

  vec3 norm = normalize(NNormal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  vec3 result = (ambient + diffuse) * objectColor;
  gl_FragColor = vec4(ambient*result, vColor[3]);//vColor;
//  gl_FragColor = vec4(NNormal,1);
}
