#include "gameObject.h"

void GameObject::update(float dt, InputManager &inputManager) {}

glm::mat4 GameObject::getTransformation() {
  glm::mat4 rotationMat = glm::toMat4(rotation);
  auto translationMat = glm::translate(glm::mat4(1.0f), position);
  return translationMat * rotationMat;
}

bool GameObject::isVisible() { return false; }
Model &GameObject::getModel() { return model; }

Light *GameObject::getObjectLight() {
  return nullptr;
}

bool GameObject::shouldCleanUp() { return cleanUpFlag; }
