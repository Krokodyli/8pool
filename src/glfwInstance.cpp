#include "glfwInstance.h"
#include <GLFW/glfw3.h>
#include <stdexcept>

GLFWInstance::GLFWInstance() {
  if (!glfwInit())
    throw std::runtime_error("Could not init GLFW");
}

GLFWInstance::~GLFWInstance() {
  glfwTerminate();
}
