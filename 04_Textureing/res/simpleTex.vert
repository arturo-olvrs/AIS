#version 410 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexTangent;
layout(location = 3) in vec3 vertexBinormal;
layout(location = 4) in vec2 texCoords;

uniform mat4 MVP; // model-view-projection Matrix
uniform mat4 MV; // model-view Matrix
uniform mat4 MVit; // model-view inverse transpose Matrix

out vec3 posViewSpace;
out vec3 N;
out vec3 T;
out vec3 B;
out vec2 tc;

void main() {
  gl_Position = MVP * vec4(vertexPosition, 1);
  posViewSpace = vec3(MV * vec4(vertexPosition, 1));

  N = normalize((MVit * vec4(vertexNormal,    0)).xyz);
  T = normalize((MVit * vec4(vertexTangent,   0)).xyz);
  B = normalize((MVit * vec4(vertexBinormal,  0)).xyz);

  tc = texCoords;
}
