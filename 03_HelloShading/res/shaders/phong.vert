#version 410 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 normalMat;

uniform vec3 lightPos;   

out vec3 N;
out vec3 P;
out vec3 LightPos;

void main()
{
	gl_Position = MVP * vec4(vertexPosition, 1.0);

    P = vec3(MV * vec4(vertexPosition, 1.0));

    N = normalize(vec3(normalMat * vec4(vertexNormal, 1)));

    LightPos = lightPos;    
}