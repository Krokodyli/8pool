#pragma once

#include <string>
#include <exception>
#include "keys.h"
#include <stdexcept>
#include "camera.h"
#include "glad.h"
#include "glfwInstance.h"
#include "inputManager.h"
#include "renderer.h"
#include "shader.h"
#include "glfw.h"
#include "shaderManager.h"
#include <iostream>

class Window {
private:
  GLFWInstance glfwInstance;

  int width, height;
  std::string title;
  GLFWwindow *glWindow;

  Camera camera;
  ShaderManager shaderManager;
  Renderer renderer;
  InputManager inputManager;

  float cameraSpeed = 6.00f;
  glm::vec3 cameraPos;
  glm::vec3 cameraDirection;
  float yaw, pitch;
  bool isMoving = true, wasPressed = false;

  void createWindow();
  void loadGlad();
  void setUpGLFW();
  void setUpOpenGL();
  void registerKeys();
  void processInput(float dt);
public:
  Window(int width, int height, std::string title);

  void init();
  void runLoop();
};
