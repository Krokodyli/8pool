#include "gameObject.h"

GameObject::GameObject() { }

GameObject::GameObject(Model model, glm::vec3 initialPos) {
  modelParts.push_back(model);
  initPhysicalObject(initialPos);
}

void GameObject::update(float dt, InputManager &inputManager) {
  updatePhysicalObject(dt);
}

std::vector<glm::mat4> GameObject::getTransformations() {
  glm::mat4 rotationMat = glm::toMat4(rotation);
  auto translationMat = glm::translate(glm::mat4(1.0f), position);
  return {translationMat * rotationMat};
}

std::vector<Model> &GameObject::getModelParts() { return modelParts; }

std::vector<Light*> GameObject::getModelLights() { return { }; }
