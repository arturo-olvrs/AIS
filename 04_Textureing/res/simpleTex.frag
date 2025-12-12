#version 410 core

uniform sampler2D td;
uniform sampler2D ts;
uniform sampler2D tNormals;

uniform mat4 MVit; // model-view inverse transpose Matrix
uniform vec4 lightPosition;
uniform mat4 AdjustmentMat;


uniform vec3 ld = vec3(0.9f, 0.9f, 0.9f); // light diffuse color
uniform vec3 ls = vec3(0.9f, 0.9f, 0.9f); // light specular color
uniform float shininess = 50.0f;

in vec2 tc;
in vec3 posViewSpace;
out vec4 color;

void main() {
  vec3 N_objectWorld_pre = normalize(texture(tNormals, tc).rgb * 2.0 - 1.0);
  vec3 N_objectWorld = normalize((AdjustmentMat * vec4(N_objectWorld_pre, 1)).xyz);


  vec3 N = normalize((MVit * vec4(N_objectWorld, 0)).xyz);
  vec3 L = normalize(lightPosition.xyz - posViewSpace);
  vec3 V = normalize(-posViewSpace);
  vec3 R = normalize(reflect(-L, N));


  vec3 diffuse  = ld * texture(td, tc).rgb * max(0.0, dot(N,L));
  vec3 specular = ls * texture(ts, tc).rgb * pow(max(0.0, dot(V,R)), shininess);

  color = vec4(diffuse+ specular, 1.0);

}
