#pragma once

#include "../../includes/glm.h"
#include "physicalObject.h"
#include "gameObject.h"

class Ball : public GameObject, public PhysicalObject {
public:
  static constexpr float ballRadius = 0.0285;
  static constexpr float ballMass = 0.165;

  Ball(Model model, glm::vec3 initialPos);

  void update(float dt, InputManager &inputManager);

  glm::mat4 getTransformation();
};
