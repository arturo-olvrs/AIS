#include <GLEnv.h>
#include <Mat4.h>
#include <GLAppKeyTranslation.h>
#include <iostream>
#include <sstream>

GLFWwindow* window;
GLuint vbo;
GLuint vao;
GLuint program;

// vertex data: position (x,y,z) + color (r,g,b)
const float triangles[] = {
    // Green, Left one
    -0.5f, -0.5f, 0.0f,   0.2f, 0.9f, 0.2f, // bottom left
     0.5f, -0.5f, 0.0f,   0.2f, 0.9f, 0.2f, // bottom right
    -0.5f,  0.5f, 0.0f,   0.2f, 0.9f, 0.2f, // top

    // Orange, Right one
    -0.5f,  0.5f, 0.0f,   0.9f, 0.5f, 0.2f, // top left
     0.5f, -0.5f, 0.0f,   0.9f, 0.5f, 0.2f, // bottom
     0.5f,  0.5f, 0.0f,   0.9f, 0.5f, 0.2f  // top right
};

// vertex shader
const char* vertexShaderSource = R"(
#version 410 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;
out vec3 color;
void main() {
    gl_Position = vec4(vPos, 1.0);
    color = vColor;
}
)";

// fragment shader
const char* fragmentShaderSource = R"(
#version 410 core
in vec3 color;
out vec4 fragColor;
void main() {
    fragColor = vec4(color, 1.0);
}
)";

static void draw() {
    GL( glClearColor(0.1f, 0.15f, 0.15f, 1.0f) );
    GL( glClear(GL_COLOR_BUFFER_BIT) );

    GL( glBindVertexArray(vao) );
    GL( glUseProgram(program) );

    GL( glDrawArrays(GL_TRIANGLES, 0, 6) );

    GL( glBindVertexArray(0) );
}

static void setupShaders() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GL( glShaderSource(vertexShader, 1, &vertexShaderSource, NULL) );
    GL( glCompileShader(vertexShader) );
    checkAndThrowShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GL( glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL) );
    GL( glCompileShader(fragmentShader) );
    checkAndThrowShader(fragmentShader);

    program = glCreateProgram();
    GL( glAttachShader(program, vertexShader) );
    GL( glAttachShader(program, fragmentShader) );
    GL( glLinkProgram(program) );
    checkAndThrowProgram(program);

    GL( glDeleteShader(vertexShader) );
    GL( glDeleteShader(fragmentShader) );
}

static void setupGeometry() {
    GL( glGenVertexArrays(1, &vao) );
    GL( glBindVertexArray(vao) );

    GL( glGenBuffers(1, &vbo) );
    GL( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
    GL( glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW) );

    // position (layout = 0)
    GL( glEnableVertexAttribArray(0) );
    GL( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0) );

    // color (layout = 1)
    GL( glEnableVertexAttribArray(1) );
    GL( glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))) );

    GL( glBindVertexArray(0) );
}

#ifndef __EMSCRIPTEN__
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLENV_KEY_ESCAPE) == GLENV_PRESS)
        glfwSetWindowShouldClose(window, true);
}

static void sizeCallback(GLFWwindow* window, int width, int height) {
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
}
#endif

int main(int argc, char** argv) {
#ifdef __EMSCRIPTEN__
    GLEnv glEnv{800,600,1,"Two Triangles",true,false,3,0,true};
#else
    GLEnv glEnv{800,600,1,"Two Triangles",true,false,4,1,true};
    glEnv.setKeyCallback(keyCallback);
    glEnv.setResizeCallback(sizeCallback);
#endif

    setupShaders();
    setupGeometry();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(draw, nullptr, 0, 1);
#else
    while (!glEnv.shouldClose()) {
        draw();
        glEnv.endOfFrame();
    }
#endif

    return EXIT_SUCCESS;
}
