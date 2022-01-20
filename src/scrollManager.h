#pragma once

#include "includes/glfw.h"

class ScrollManager {
private:
  static double xDelta, yDelta;

  static void scrollCallback(GLFWwindow *window, double xOffset,
                             double yOffset);
public:
  ScrollManager(GLFWwindow *window);

  void getScrollDelta(double &x, double &y);
  void resetScrollDelta();
};
