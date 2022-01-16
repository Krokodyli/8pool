#pragma once

#include "includes/glfw.h"
#include <unordered_map>

class InputManager {
private:
  const static int maxKeyCode = 256;
  std::unordered_map<int, int> glfwKeyCodeToKeyCode;

  bool keyStatus[maxKeyCode + 1];
  bool oldKeyStatus[maxKeyCode + 1];

  double mouseX, mouseY;
  double oldMouseX, oldMouseY;

public:
  InputManager();

  bool registerKey(int glfwCode, int keyCode);

  void init(GLFWwindow *glWindow);
  void update(GLFWwindow *glWindow);

  bool isKeyDown(int keyCode);
  bool isKeyPressed(int keyCode);

  double getMouseX();
  double getMouseY();
  void getMousePos(double &x, double &y);

  double getMouseDeltaX();
  double getMouseDeltaY();
  void getMouseDelta(double &x, double &y);
};
