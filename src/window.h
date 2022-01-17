#pragma once

#include "includes/glad.h"
#include <chrono>
#include "glfwInstance.h"
#include "inputManager.h"
#include "scene/scene.h"
#include "scene/mainScene.h"
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
