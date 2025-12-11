#version 410 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 texCoords;

uniform mat4 MVP; // model-view-projection Matrix
uniform mat4 MV; // model-view Matrix

out vec2 tc;
out vec3 posViewSpace;

void main() {
  gl_Position = MVP * vec4(vertexPosition, 1);
  posViewSpace = vec3(MV * vec4(vertexPosition, 1));
  tc = texCoords;
}
