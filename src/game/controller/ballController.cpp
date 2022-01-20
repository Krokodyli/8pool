#include "ballController.h"

BallController::BallController() : moveFlag(true) {}

void BallController::init(Ball &ball) {
  moveFlag = true;
}

void BallController::update(float dt, InputManager &inputManager) {
  if(inputManager.isKeyPressed(KEY_MOVE_TOGGLE))
    moveFlag = !moveFlag;
}

void BallController::control(Ball &ball) {}

bool BallController::getMoveFlag() {
  return moveFlag;
}
