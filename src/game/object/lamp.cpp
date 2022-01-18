#include "lamp.h"

Lamp::Lamp(Model model, glm::vec3 initialPos) {
  this->model = model;
  initPhysicalObject(initialPos, 1.0f);
  initLight();
}

Light *Lamp::getObjectLight() {
  return &light;
}

void Lamp::update(float dt, InputManager &inputManager) {
  light.position = position;
}

void Lamp::initLight() {
  light.lightType = LightType::point;

  light.position = position;

  light.attenuation = glm::vec3(1.0f, 0.00f, 0.0f);

  light.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
  light.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
  light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
}
