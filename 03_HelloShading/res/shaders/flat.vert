#version 410 core

layout(location = 0) in vec3 vertexPosition;  // vertex position in object space
layout(location = 1) in vec3 vertexNormal;    // vertex normal in object space

uniform mat4 MVP; // model-view-projection Matrix
uniform mat4 modelMat;   // Model matrix
uniform mat4 normalMat;  // Normal matrix

uniform vec3 lightPos;   // Position of point light in model space world space
uniform vec3 viewPos;    // Position of camera in model space

uniform vec3 kd; // material diffuse color

flat out vec4 fragColor;

void main()
{
	gl_Position = MVP * vec4(vertexPosition, 1);

	// ----- Compute vectors for lighting -----

    // Position in model space
    vec3 P = vec3(modelMat * vec4(vertexPosition, 1.0));

    // Correctly transformed normal
    vec3 N = normalize(vec3(normalMat * vec4(vertexNormal, 1)));

    // Light direction
    vec3 L = normalize(lightPos - P);

    // View direction
    vec3 V = normalize(viewPos - P);

    // Reflection vector
    vec3 R = reflect(-L, N);

	// ----- Light coefficients -----
    vec3 LightAmbient  = vec3(0.9);
    vec3 LightDiffuse  = vec3(0.9);
    vec3 LightSpecular = vec3(0.9);

    // ----- Material coefficients -----
    vec3 Ka = vec3(0.05);  // ambient
    vec3 Ks = vec3(1.0);   // specular
    float shininess = 50.0;



	// ----- Phong illumination -----

    vec3 ambient = LightAmbient * Ka;
    vec3 diffuse = LightDiffuse * kd * max(dot(N, L), 0.0);
    vec3 specular = LightSpecular * Ks * pow(max(dot(V, R), 0.0), shininess);


	// Final color
    fragColor = vec4(ambient + diffuse + specular,1);
}
