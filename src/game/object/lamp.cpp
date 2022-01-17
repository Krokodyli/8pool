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
  light.position = position;
  light.lightType = LightType::point;
  light.attenuation = glm::vec3(1.0, 0.7, 1.8);
  light.ambient = glm::vec3(0.5f);
  light.diffuse = glm::vec3(0.5f);
  light.specular = glm::vec3(0.5f);
}
