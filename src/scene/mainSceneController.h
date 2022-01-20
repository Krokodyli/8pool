#pragma once

#include "../camera.h"
#include "../game/object/ball.h"
#include "../game/object/lamp.h"
#include "../game/object/robot.h"
#include "../renderer.h"
#include "../inputManager.h"
#include "../keys.h"
#include <memory>

enum class ControllerMode
{
  freeCamera,
  robotCamera,
  ballCamera
};

class MainSceneController
{
private:
  ControllerMode mode;
  std::unique_ptr<InputManager> inputManager;

  Camera freeCamera;
  glm::vec3 freeCameraPos;
  float freeCameraYaw;
  float freeCameraPitch;

  Camera robotCamera;
  RobotController robotController;
  BallController ballController;
  std::vector<std::unique_ptr<LampController>> lampControllers;

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
  void updateRenderer(float dt, Renderer &renderer,
                      ResourceManager &resourceManager);

  ControllerMode getCurrentMode();
  InputManager *getInputManager();

  void setFollowedBall(Ball *ball);
  void setRobot(Robot *robot);
  void setBalls(std::vector<Ball *> &balls);
  void setLamps(std::vector<Lamp *> &lamps);
};
