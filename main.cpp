#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <iostream>

const char *vertexShaderSource = R"(
#version 120
attribute vec3 aPos;
void main()
{
	gl_Position = vec4(aPos, 1.0);
}
)";
const char *fragmentShaderSource = R"(
#version 120
void main()
{
	gl_FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
)";

void window_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

/*
 * OpenGL works in 3d. It takes vecotors, 3D Coordinates and converts to 2D
 *
 * i. So it takes a collection of vertices
 *
 * ii. Takes it into the graphics pipeline
 *
 * iii. PipleineFlow -> vertex_shader -> geometry_s -> primitive -> fragment
 *
 * For now, we mostly need to interact with the vertex and fragment
 * as the geometry shader is optional, and those are required.
 *
 * OPENGL will only render graphics btwn  -1.0 and 1.0 on all 3 axes, x, y, z
 * */

void vertexLoader() {
  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
  // vertex buffer
  unsigned int VBO;
  // glGenBuffers(GLsizei size, GLuint* buffers);
  // Generates buffer ids and stores them into an array in VBO
  glGenBuffers(1, &VBO);
  // glBuffer(bound_buffer, sizeof data, data, MGMNT)
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // enum class Mgmt { GL_STATIC_DRAW, GL_STREAM_DRAW, GL_DYNAMIC_DRAW };
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
};

int main() {
  std::cout << "glfw loaded\n\n";

  if (!glfwInit()) {
    std::cerr << "failed to initialise glfw\n";
    return -1;
  }

  GLFWwindow *window = glfwCreateWindow(800, 600, "ARCHIVES", NULL, NULL);
  if (!window) {
    std::cerr << "failed to open window\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  const GLubyte *version = glGetString(GL_VERSION);
  const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cout << "OpenGl Version -> " << version << "\n";
  std::cout << "GlSl Version -> " << glslVersion << "\n";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  vertexLoader();
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "shaderCompilationFailure\n" << infoLog << "\n";
    return -1;
  }
  // loading fragment shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "fragmentShaderCompilationFailure:\n" << infoLog << "\n";
    return -1;
  }

  std::cout << "fragment and vertex shaders compiled\n";
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  std::cout << "ShaderID -> " << shaderProgram << "\n";
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "shaderProgramError\n" << infoLog << "\n";
    return -1;
  }
  std::cout << "shader program compiled\ncleaning up...\n";

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
  unsigned int VBO, VAO;
  // glGenVertexArrays(1, &VAO);
  // glBindVertexArray(VAO);
  //
  // glBindGenBuffers(1, &VBO);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  //
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // glBindVertexArray(0);
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.4f, 2.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  std::cout << "window terminatedd!!!\n";
  return 0;
}

void window_size_callback(GLFWwindow *window, int width, int height) {
  std::cout << "user resized window -> " << width << " " << " " << height
            << "\n";
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    std::cout << "User hit escape key -> " << GLFW_PRESS << "\n";
  };

  return;
}
