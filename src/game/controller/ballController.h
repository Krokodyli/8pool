#pragma once

#include "../../input/inputManager.h"
#include "../../scene/keys.h"

class Ball;

class BallController {
private:
  bool moveFlag;
public:
  BallController();
  void init(Ball &ball);
  void update(float dt, InputManager &inputManager);
  void control(Ball &ball);
  bool getMoveFlag();
};
