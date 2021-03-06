#pragma once

#include <unordered_map>
#include "../includes/glfw.h"
#include "scrollManager.h"

class InputManager {
private:
  GLFWwindow *glWindow;

  const static int maxKeyCode = 256;
  std::unordered_map<int, int> glfwKeyCodeToKeyCode;

  bool keyStatus[maxKeyCode + 1];
  bool oldKeyStatus[maxKeyCode + 1];

  double mouseX, mouseY;
  double oldMouseX, oldMouseY;

  ScrollManager scrollManager;

public:
  InputManager(GLFWwindow *window);

  bool registerKey(int glfwCode, int keyCode);

  void init();
  void update();

  bool isKeyDown(int keyCode);
  bool isKeyPressed(int keyCode);

  double getMouseX();
  double getMouseY();
  void getMousePos(double &x, double &y);

  double getMouseDeltaX();
  double getMouseDeltaY();
  void getMouseDelta(double &x, double &y);

  void getScrollDelta(double &x, double &y);
  void resetScrollDelta();
};
