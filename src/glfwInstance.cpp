#include "glfwInstance.h"

GLFWInstance::GLFWInstance() {
  if (!glfwInit())
    throw std::runtime_error("Could not init GLFW");
}

GLFWInstance::~GLFWInstance() {
  glfwTerminate();
}
