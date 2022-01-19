#pragma once

#include "../../inputManager.h"
#include "../../camera.h"

class Robot;

class RobotController {
private:
  glm::vec3 eyesOffset;
  float yaw, pitch;
  glm::vec3 dir;
  bool action;

  glm::vec3 robotPos;
  glm::quat robotRotation;
public:
  void init(Robot &robot);
  void update(float dt, InputManager &inputManager);
  void updateEyeCamera(Camera &camera);
  void control(Robot &robot);
};
