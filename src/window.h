#pragma once

#include <string>
#include <exception>
#include <stdexcept>
#include "camera.h"
#include "../build/_deps/glad-build/include/glad/glad.h"
#include "renderer.h"
#include "shader.h"
#include <GLFW/glfw3.h>

class Window {
private:
  int width, height;
  std::string title;
  GLFWwindow *glWindow;

  Camera camera;
  Shader shader;
  Renderer renderer;

  double mouseX, mouseY;
  float cameraSpeed = 0.05f;
  glm::vec3 cameraPos;
  glm::vec3 cameraDirection;
  float yaw, pitch;
  bool isMoving = true, wasPressed = false;

  void initGLFW();
  void createWindow();
  void loadGlad();
  void setUpGLFW();
  void setUpOpenGL();
  void processInput(float dt);
public:
  Window(int width, int height, std::string title);
  ~Window();
  void init();
  void runLoop();
};
