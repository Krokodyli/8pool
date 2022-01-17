#include "gameObject.h"

void GameObject::update(float dt, InputManager &inputManager) { }

glm::mat4 GameObject::getTransformation() {
  return glm::mat4(1.0f);
}

Model &GameObject::getModel() {
  return model;
}

bool GameObject::shouldCleanUp() {
  return cleanUpFlag;
}
