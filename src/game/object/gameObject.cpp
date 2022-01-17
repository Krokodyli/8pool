#include "gameObject.h"

void GameObject::update(float dt, InputManager &inputManager) { }

glm::mat4 GameObject::getTransformation() {
  glm::mat4 rotationMat = glm::toMat4(rotation);
  auto translationMat = glm::translate(glm::mat4(1.0f), position);
  return translationMat * rotationMat;
}

Model &GameObject::getModel() {
  return model;
}

bool GameObject::shouldCleanUp() {
  return cleanUpFlag;
}
