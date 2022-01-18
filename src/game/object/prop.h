#pragma once

#include "physicalObject.h"
#include "gameObject.h"

class Prop : public GameObject {
public:
  Prop(Model model, glm::vec3 initialPos);

  virtual void update(float dt, InputManager &inputManager);
};
