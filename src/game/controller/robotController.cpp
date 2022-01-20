#include "robotController.h"
#include "../object/robot.h"
#include "../../keys.h"

void RobotController::init(Robot &robot) {
  eyesOffset = glm::vec3(0.0f, Robot::headSize / 4.0f,
                         Robot::headSize / 2.0f + 0.02f);
  robotPos = robot.getPosition();
  robotRotation = robot.getRotation();
  yaw = -90.0f;
  pitch = 0.0f;
  action = false;
}

void RobotController::update(float dt, InputManager &inputManager) {
  float robotSpeed = 2.0f;
  double sensivity = 0.1;
  double deltaX, deltaY;
  inputManager.getMouseDelta(deltaX, deltaY);
  deltaX *= sensivity;
  deltaY *= sensivity;
  yaw += deltaX;
  pitch -= deltaY;
  pitch = std::min(pitch, 89.0f);
  pitch = std::max(pitch, -89.0f);

  dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  dir.y = sin(glm::radians(pitch));
  dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  dir = glm::normalize(dir);
  robotRotation = glm::quatLookAt(dir, glm::vec3(0.0f, 1.0f, 0.0f));

  if (inputManager.isKeyDown(KEY_FORWARD))
    robotPos += dir * robotSpeed * dt;
  if (inputManager.isKeyDown(KEY_BACKWARD))
    robotPos -= dir * robotSpeed * dt;
  if (inputManager.isKeyDown(KEY_LEFT)) {
    auto moveDir = glm::normalize(glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f)));
    robotPos -= moveDir * robotSpeed * dt;
  }
  if (inputManager.isKeyDown(KEY_RIGHT)) {
    auto moveDir = glm::normalize(glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f)));
    robotPos += moveDir * robotSpeed * dt;
  }

  action = inputManager.isKeyPressed(KEY_ACTION);
}

void RobotController::updateEyeCamera(Camera &camera) {
  auto eyesPos = robotPos + glm::rotate(robotRotation, eyesOffset);
  camera.lookAt(eyesPos, eyesPos + dir, glm::vec3(0.0f, 1.0f, 0.0f));
}

void RobotController::control(Robot &robot) {
  robot.setRotation(robotRotation);
  robot.setPosition(robotPos);
  if(action)
    robot.toggleLight();
}
