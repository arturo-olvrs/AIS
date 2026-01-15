#version 410 core

layout(location = 0) in vec3 vertexPosition; 
out vec3 texCoords;

uniform mat4 MVP;

void main()
{
	texCoords = vertexPosition;
	vec4 pos = MVP * vec4(vertexPosition, 1);
	gl_Position = pos.xyww;
}
