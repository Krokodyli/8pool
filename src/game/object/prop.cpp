#include "prop.h"

Prop::Prop(Model model, glm::vec3 initialPos) {
  this->model = model;
  initPhysicalObject(initialPos, 5.0f);
}

void Prop::update(float dt, InputManager &inputManager) { }
