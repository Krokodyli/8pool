#include "lampController.h"
#include "../controller/ballController.h"
#include "../object/lamp.h"

LampController::LampController(int toggleKey, float radius, float rotationTime,
                               glm::vec3 rotationAxis)
  : isTurnedOn(true), toggleKey(toggleKey), isRotating(true), radius(radius),
      rotationTime(rotationTime), rotationAxis(rotationAxis) {}

LampController::LampController(int toggleKey)
    : isTurnedOn(true), toggleKey(toggleKey), isRotating(false) {}

void LampController::init(Lamp &lamp) {
  time = 0.0f;
  center = lamp.getPosition();
}

void LampController::update(float dt, InputManager &inputManager) {
  if (inputManager.isKeyPressed(toggleKey))
    isTurnedOn = !isTurnedOn;
  if (isRotating && isTurnedOn) {
    time += dt;
  }
}

void LampController::control(Lamp &lamp) {
  if(isRotating && isTurnedOn) {
    auto angle = time / rotationTime;
    auto rotation = glm::rotate(glm::mat4(1.0f), angle, rotationAxis);
    auto newPos = glm::mat3(rotation) * glm::vec3(radius, 0.0f, 0.0f);
    lamp.setPosition(newPos + center);
  }
}

bool LampController::isLampTurnedOn() { return isTurnedOn; }
