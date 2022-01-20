#include "lampController.h"
#include "../controller/ballController.h"
#include "../object/lamp.h"

LampController::LampController(int toggleKey, float speed,
                               glm::vec3 rotationCenter, glm::vec3 rotationAxis)
    : isTurnedOn(true), toggleKey(toggleKey), isRotating(true), speed(speed),
      rotationCenter(rotationCenter), rotationAxis(rotationAxis) {}

LampController::LampController(int toggleKey)
    : isTurnedOn(true), toggleKey(toggleKey), isRotating(false) {}

void LampController::init(Lamp &lamp) {}

void LampController::update(float dt, InputManager &inputManager) {
  if (inputManager.isKeyPressed(toggleKey))
    isTurnedOn = !isTurnedOn;
}

void LampController::control(Lamp &lamp) {
  if (isRotating && isTurnedOn) {
    auto radiusVec = lamp.getPosition() - rotationCenter;
    auto tangentDir = glm::normalize(glm::cross(rotationAxis, radiusVec));
    lamp.setVelocity(tangentDir * speed);
  }
}

bool LampController::isLampTurnedOn() { return isTurnedOn; }
