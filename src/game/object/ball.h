#pragma once

#include "../../includes/glm.h"
#include "../controller/ballController.h"
#include "gameObject.h"
#include "physicalObject.h"

class Ball : public GameObject {
private:
  BallController *controller;

public:
  static constexpr float ballRadius = 0.0285;
  static constexpr float ballMass = 0.165;

  Ball(Model model, glm::vec3 initialPos, BallController *controller = nullptr);

  virtual void update(float dt);

  void setController(BallController *newController);
};
