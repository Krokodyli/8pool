#pragma once

#include "../../includes/glm.h"
#include "physicalObject.h"
#include "gameObject.h"

class Ball : public GameObject {
public:
  static constexpr float ballRadius = 0.0285;
  static constexpr float ballMass = 0.165;

  Ball(Model model, glm::vec3 initialPos);

  virtual void update(float dt);
};
