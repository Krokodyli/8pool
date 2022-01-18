#pragma once

#include "gameObject.h"

class Lamp : public GameObject {
private:
  Light light;

  void initLight();
public:
  Lamp(Model model, glm::vec3 initialPos);

  virtual void update(float dt, InputManager &inputManager);

  virtual std::vector<Light *> getModelLights();
};
