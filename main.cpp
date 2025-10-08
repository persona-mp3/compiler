#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n "
    "{\n"
    "    gl_Position - vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

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
  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glClearColor(0.2f, 0.3f, 0.4f, 2.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
    glfwSetWindowSizeCallback(window, window_size_callback);
    // glfwSetWindowOpacity(window, 0.2f);
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
