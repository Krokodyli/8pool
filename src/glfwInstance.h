#pragma once

#include "glfw.h"
#include <stdexcept>

// class that handles GLFW initialization/cleanup
class GLFWInstance {
public:
  GLFWInstance();
  ~GLFWInstance();
};
