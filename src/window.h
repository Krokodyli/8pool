#pragma once

#include "camera.h"
#include "glad.h"
#include "resourceManager/resourceManager.h"
#include "texture.h"
#include "meshes/cuboidMesh.h"
#include "meshes/sphereMesh.h"
#include <chrono>
#include "glfw.h"
#include "glfwInstance.h"
#include "inputManager.h"
#include "keys.h"
#include "renderer.h"
#include "shader.h"
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

  Camera camera;
  ResourceManager resourceManager;
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
