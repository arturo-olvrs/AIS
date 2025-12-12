#version 410 core

in vec3 posViewSpace;
in vec3 N;
in vec3 T;
in vec3 B;
in vec2 tc;

uniform sampler2D td;
uniform sampler2D ts;
uniform sampler2D tNormals;

uniform vec4 lightPosition;

uniform vec3 ld = vec3(0.9f, 0.9f, 0.9f); // light diffuse color
uniform vec3 ls = vec3(0.9f, 0.9f, 0.9f); // light specular color
uniform float shininess = 50.0f;

out vec4 color;

void main() {
  vec3 kd = texture(td, tc).rgb;
  vec3 ks = texture(ts, tc).rgb;
  vec3 normalMap = normalize(2 * (texture(tNormals, tc).xyz - vec3(0.5)));

  vec3 N = normalize(N);
  vec3 T = normalize(T);
  vec3 B = normalize(B);

  mat3 tbnMat = mat3(T,B,N);
  vec3 real_N = normalize(tbnMat * normalMap);


  vec3 L = normalize(lightPosition.xyz - posViewSpace);
  vec3 V = normalize(-posViewSpace);
  vec3 R = normalize(reflect(-L, real_N));


  vec3 diffuse  = ld * kd * max(0.0, dot(real_N,L));
  vec3 specular = ls * ks * pow(max(0.0, dot(V,R)), shininess);

  color = vec4(diffuse+ specular, 1.0);
}
