#pragma once

#include "../inputManager.h"
#include "../game/object/ball.h"
#include "../camera.h"
#include "../keys.h"
#include "../game/object/robot.h"
#include <memory>

enum class ControllerMode { freeCamera, robotCamera, ballCamera };

class MainSceneController {
private:
  ControllerMode mode;
  std::unique_ptr<InputManager> inputManager;

  Camera freeCamera;
  glm::vec3 freeCameraPos;
  float freeCameraYaw;
  float freeCameraPitch;

  Camera robotCamera;
  std::unique_ptr<RobotController> robotController;

  Camera ballCamera;
  glm::vec3 ballCameraPos;
  Ball *followedBall;

  void init();
  void updateMode();
  void updateFreeCameraMode(float dt);
  void updateRobotCameraMode(float dt);
  void updateBallCameraMode(float dt);

public:
  MainSceneController(std::unique_ptr<InputManager> inputManager,
                      float aspectRatio);

  Camera *getCurrentCamera();

  void update(float dt);

  ControllerMode getCurrentMode();
  InputManager* getInputManager();
  void setFollowedBall(Ball *ball);
  void setRobot(Robot *robot);
};
