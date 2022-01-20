#pragma once

#include "gameObject.h"
#include "../controller/lampController.h"

class Lamp : public GameObject {
private:
  Light light;

  LampController *controller;

  void initLight();
public:
  Lamp(Model model, glm::vec3 initialPos);

  virtual void update(float dt);

  virtual std::vector<Model> &getModelParts();
  virtual std::vector<Light *> getModelLights();

  void setController(LampController *newController);
};
