#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D texture;
varying vec2 vTexCoord;
varying vec4 vColor;
varying vec3 vNormal;
varying vec3 vPosition;


void main() {
  //
  //
  vec3 lightPos = vec3(0.0,0.0,0.0);
  vec3 lightColor = vec3(1.0,1.0,1.0);
  vec3 objectColor = vec3(vColor[0],vColor[1],vColor[2]);

  float ambientStrength = 0.8;
  vec3 ambient = ambientStrength * lightColor;

  vec3 norm = normalize(vNormal);
  vec3 lightDir = normalize(lightPos -  vPosition);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  vec3 result = (ambient + diffuse) * objectColor;

  if(vTexCoord.x < 0.0 && vTexCoord.y < 0.0) {
    gl_FragColor = vec4(ambient*result, vColor[3]);
  } else {
    gl_FragColor = texture2D(texture, vTexCoord) * vec4(ambient*result, vColor[3]);
//    gl_FragColor = texture2D(texture, vTexCoord) * vec4(1.0,1.0,1.0,1.0);
  }
//  gl_FragColor = vec4(ambient*result, vColor[3]);//vColor;
//  gl_FragColor = texture2D(texture, textureCoord) * vec4(ambient*result, vColor[3]);//vColor;

//  gl_FragColor = vec4(NNormal,1);
}
