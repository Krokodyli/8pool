#include "inputManager.h"

InputManager::InputManager(GLFWwindow *glWindow) : glWindow(glWindow) {
  for(int i = 0; i <= maxKeyCode; i++) {
    keyStatus[i] = false;
    oldKeyStatus[i] = false;
  }
}

bool InputManager::registerKey(int glfwCode, int keyCode) {
  if(keyCode < 0 || keyCode > maxKeyCode)
    return false;

  glfwKeyCodeToKeyCode[glfwCode] = keyCode;

  return true;
}

void InputManager::init() {
  update();
}

void InputManager::update() {
  for(const auto &entry : glfwKeyCodeToKeyCode) {
    oldKeyStatus[entry.second] = keyStatus[entry.second];
    bool keyDown = (glfwGetKey(glWindow, entry.first) == GLFW_PRESS);
    keyStatus[entry.second] = keyDown;
  }

  oldMouseX = mouseX;
  oldMouseY = mouseY;
  glfwGetCursorPos(glWindow, &mouseX, &mouseY);
}

bool InputManager::isKeyDown(int keyCode) {
  if (keyCode < 0 || keyCode > maxKeyCode)
    return false;
  return keyStatus[keyCode];
}

bool InputManager::isKeyPressed(int keyCode) {
  if (keyCode < 0 || keyCode > maxKeyCode)
    return false;
  return keyStatus[keyCode] && !oldKeyStatus[keyCode];
}

double InputManager::getMouseX() { return mouseX; }
double InputManager::getMouseY() { return mouseY; }

void InputManager::getMousePos(double &x, double &y) {
  x = mouseX;
  y = mouseY;
}

double InputManager::getMouseDeltaX() { return mouseX - oldMouseX; }
double InputManager::getMouseDeltaY() { return mouseY - oldMouseY; }

void InputManager::getMouseDelta(double &x, double &y) {
  x = mouseX - oldMouseX;
  y = mouseY - oldMouseY;
}
