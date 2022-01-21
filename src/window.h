#pragma once

#include "utils/filesystemHelper.h"
#include "utils/glfwInstance.h"
#include "includes/glad.h"
#include "input/inputManager.h"
#include "scene/mainScene.h"
#include "scene/scene.h"
#include <chrono>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

class Window {
private:
  GLFWInstance glfwInstance;

  int width, height;
  std::string title;
  GLFWwindow *glWindow;

  void createWindow();
  void loadGlad();
  void setUpGLFW();
  void setUpOpenGL();

public:
  Window(int width, int height, std::string title);

  void init();
  void runLoop();
};
