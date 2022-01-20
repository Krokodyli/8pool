#pragma once

#include "../../includes/glm.h"
#include "../../inputManager.h"
#include "../../keys.h"

class Lamp;

class LampController {
private:
  bool isTurnedOn;
  int toggleKey;

  bool isRotating;
  float speed;
  glm::vec3 rotationCenter;
  glm::vec3 rotationAxis;

  glm::vec3 calculatedVelocity;

public:
  LampController(int toggleKey, float speed,
                 glm::vec3 rotationCenter, glm::vec3 rotationAxis);
  LampController(int toggleKey);

  void init(Lamp &lamp);
  void update(float dt, InputManager &inputManager);
  void control(Lamp &lamp);

  bool isLampTurnedOn();
};
