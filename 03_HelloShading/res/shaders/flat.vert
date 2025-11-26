#version 410 core

// ----------- Inputs from VAO --------------
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

// ----------- Uniforms --------------
uniform mat4 MVP;        // Model-View-Projection matrix
uniform mat4 MV;         // Model-View matrix
uniform mat3 NormalMat;  // Normal matrix

uniform vec3 lightPos;   // Position of point light in world space
uniform vec3 viewPos;    // Position of camera

// Material parameters
uniform vec3 Kd;  // Diffuse color (set in your C++ via kdUniform)

// Output to fragment shader (FLAT!)
flat out vec4 fragColor;

void main()
{
    // Transform vertex
    gl_Position = MVP * vec4(vertexPosition, 1.0);

    // ----- Compute vectors for lighting -----

    // Position in Eye space
    vec3 P = vec3(MV * vec4(vertexPosition, 1.0));

    // Correctly transformed normal
    vec3 N = normalize(NormalMat * vertexNormal);

    // Light direction
    vec3 L = normalize(lightPos - P);

    // View direction
    vec3 V = normalize(- P);    // camera at origin

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

    // ----- Phong illumination (computed per VERTEX) -----

    vec3 ambient = LightAmbient * Ka;
    vec3 diffuse = LightDiffuse * Kd * max(dot(N, L), 0.0);
    vec3 specular = LightSpecular * Ks * pow(max(dot(V, R), 0.0), shininess);

    // Final color
    fragColor = vec4(ambient + diffuse + specular,1);
}
