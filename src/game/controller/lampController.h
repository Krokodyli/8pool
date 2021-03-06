#pragma once

#include "../../includes/glm.h"
#include "../../input/inputManager.h"
#include "../../scene/keys.h"

class Lamp;

class LampController {
private:
  bool isTurnedOn;
  int toggleKey;

  bool isRotating;

  glm::vec3 center;
  float radius;
  float rotationTime;
  glm::vec3 rotationAxis;

  float time;

public:
  LampController(int toggleKey, float radius, float rotationTime,
                 glm::vec3 rotationAxis);

  LampController(int toggleKey);

  void init(Lamp &lamp);
  void update(float dt, InputManager &inputManager);
  void control(Lamp &lamp);

  bool isLampTurnedOn();
};
