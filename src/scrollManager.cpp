#include "scrollManager.h"

double ScrollManager::xDelta = 0.0;
double ScrollManager::yDelta = 0.0;

ScrollManager::ScrollManager(GLFWwindow *window) {
  xDelta = yDelta = 0.0;
  glfwSetScrollCallback(window, scrollCallback);
}

void ScrollManager::getScrollDelta(double &x, double &y) {
  x = xDelta;
  y = yDelta;
}

void ScrollManager::scrollCallback(GLFWwindow *window, double xOffset,
                                   double yOffset) {
  xDelta += xOffset;
  yDelta += yOffset;
}

void ScrollManager::resetScrollDelta() {
  xDelta = 0;
  yDelta = 0;
}
