#version 410 core

in vec3 N;
in vec3 P;
in vec3 LightPos;

// Uniforms (deben ser consistentes con el Vertex Shader)
uniform vec3 kd; // material diffuse color

out vec4 fragColor;

void main()
{
    vec3 N = normalize(N);
    
    // 1. Vectores de iluminación por fragmento (P está en World Space)
    vec3 L = normalize(LightPos - P);
    vec3 V = normalize( - P);
    vec3 R = reflect(-L, N);

    // ----- Light coefficients -----
    vec3 LightAmbient  = vec3(0.9);
    vec3 LightDiffuse  = vec3(0.9);
    vec3 LightSpecular = vec3(0.9);

    // ----- Material coefficients -----
    vec3 Ka = vec3(0.05);  // ambient
    vec3 Ks = vec3(1.0);   // specular
    float shininess = 50.0;
    
    
    // 2. Cálculos de Iluminación de Phong por FRAGMENTO
    
    vec3 ambient = LightAmbient * Ka;
    vec3 diffuse = LightDiffuse * kd * max(dot(N, L), 0.0);
    vec3 specular = LightSpecular * Ks * pow(max(dot(V, R), 0.0), shininess);
    
    // Color Final
    fragColor = vec4(ambient + diffuse + specular, 1.0);
}