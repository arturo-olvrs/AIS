#include <GLEnv.h>
#include <Mat4.h>
#include <GLAppKeyTranslation.h>

#include <iostream>
#include <sstream>

GLuint vbo;
GLuint vao;
GLuint program;

constexpr float triangle1[] = {
  -0.5f,  0.5f, 0.0f, 0.9f, 0.5f, 0.2f,// top left
  0.5f,  0.5f, 0.0f, 0.9f, 0.5f, 0.2f, // top right
  0.5f, -0.5f, 0.0f, 0.9f, 0.5f, 0.2f, // bottom right
  -0.5f,  0.5f, 0.0f, 0.2f, 0.9f, 0.2f,// top left
  0.5f, -0.5f, 0.0f, 0.2f, 0.9f, 0.2f,// bottom right
  -0.5f, -0.5f, 0.0f, 0.2f, 0.9f, 0.2f// bottom left
};

const GLchar* vertexShaderSource{
#ifdef __EMSCRIPTEN__
R"(#version 300 es 
in vec3 vPos;
in vec3 vColor;
out vec3 color;
void main()
{
  gl_Position = vec4(vPos, 1.0);
  color = vColor;
}
)"
#else
R"(#version 410 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;
out vec3 color;
void main()
{
  gl_Position = vec4(vPos, 1.0);
  color = vColor;
}
)"
#endif
};


const GLchar* framentShaderSource{
#ifdef __EMSCRIPTEN__
R"(#version 300 es
precision mediump float;
out vec4 fragColor;
in vec3 color;
void main()
{
  fragColor = vec4(color, 1.0);
}
)"
#else
R"(#version 410 core
out vec4 fragColor;
in vec3 color;
void main()
{
  fragColor = vec4(color, 1.0);
}
)"
#endif
};

static void draw(void* arg=nullptr) {
  GL( glClearColor(0.1f, 0.15f, 0.15f, 1.0f) );
  GL( glClear(GL_COLOR_BUFFER_BIT) );

  GL( glBindVertexArray(vao) );
  GL( glUseProgram(program) );
  GL( glDrawArrays(GL_TRIANGLES, 0, 6) );

  GL( glBindVertexArray(0) );
}

static void setupShaders() {
  // create the vertex shader
  const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GL( glShaderSource(vertexShader, 1, &vertexShaderSource, NULL) );
  GL( glCompileShader(vertexShader) );
  checkAndThrowShader(vertexShader);

  // create the fragment shader for orange tris
  const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  GL( glShaderSource(fragmentShader, 1, &framentShaderSource, NULL) );
  GL( glCompileShader(fragmentShader) );
  checkAndThrowShader(fragmentShader);

  // link shaders into programs
  program = glCreateProgram();
  GL( glAttachShader(program, vertexShader) );
  GL( glAttachShader(program, fragmentShader) );
  GL( glLinkProgram(program) );
  checkAndThrowProgram(program);

  GL( glDeleteShader(vertexShader) );
  GL( glDeleteShader(fragmentShader) );
}

static void setupGeometry() {
  GL( glGenBuffers(1, &vbo) );

  // define VAO for triangle
  GL( glGenVertexArrays(1, &vao) );
  GL( glBindVertexArray(vao) );

  // upload vertex positions to VBO
  GL( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
  GL( glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW) );

  GL( glEnableVertexAttribArray(0) );
  GL( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0) );

  GL( glEnableVertexAttribArray(1) );
  GL( glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float))));

  GL( glBindVertexArray(0) );
}

static void checkProgramLinkStatus(GLuint programId) {
  GLint success;
  glGetProgramiv(programId, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(programId, 512, NULL, infoLog);
    std::cout << "Error: Program link failed.\n" << infoLog << std::endl;
  }
}

static void checkShaderCompileStatus(GLuint shaderId) {
  GLint success;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
    std::cout << "Error: Shader compilation failed.\n" << infoLog << std::endl;
  }
}

#ifndef __EMSCRIPTEN__
static void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                 int mods) {
  if (glfwGetKey(window, GLENV_KEY_ESCAPE) == GLENV_PRESS)
    glfwSetWindowShouldClose(window, true);
}

static void sizeCallback(GLFWwindow* window, int width, int height) {
  int w, h;
  glfwGetFramebufferSize(window, &w, &h);
  GL( glViewport(0, 0, w, h) );
}

#endif

int main(int argc, char** argv) {
#ifdef __EMSCRIPTEN__
  GLEnv glEnv{800,600,1,"My First OpenGL Program",true,false,3,0,true};
#else
  GLEnv glEnv{800,600,1,"My First OpenGL Program",true,false,4,1,true};
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
