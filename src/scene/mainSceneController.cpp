#include "mainSceneController.h"

MainSceneController::MainSceneController(
    std::unique_ptr<InputManager> inputManager, float aspectRatio)
    : inputManager(std::move(inputManager)),
      freeCamera(glm::radians(45.0f), aspectRatio),
      robotCamera(glm::radians(45.0f), aspectRatio),
      ballCamera(glm::radians(45.0f), aspectRatio) {
  init();
}

Camera *MainSceneController::getCurrentCamera() {
  switch (mode) {
  case ControllerMode::freeCamera:
    return &freeCamera;
  case ControllerMode::robotCamera:
    return &robotCamera;
  case ControllerMode::ballCamera:
    return &ballCamera;
  default:
    return nullptr;
  }
}

void MainSceneController::update(float dt) {
  inputManager->update();

  updateMode();
  updateFreeCameraMode(dt);
  updateRobotCameraMode(dt);
  updateBallCameraMode(dt);
}

ControllerMode MainSceneController::getCurrentMode() { return mode; }

InputManager *MainSceneController::getInputManager() {
  return inputManager.get();
}

void MainSceneController::setFollowedBall(Ball *ball) {
  followedBall = ball;
}

void MainSceneController::setRobot(Robot *robot) {
  robotController = std::make_unique<RobotController>();
  robot->setController(robotController.get());
}

void MainSceneController::init() {
  mode = ControllerMode::freeCamera;

  freeCameraPos = glm::vec3(0.0f, 1.0f, -2.0f);
  freeCameraPitch = -30.0f;
  freeCameraYaw = 90.0f;

  ballCameraPos = glm::vec3(-1.0f, 2.0f, 0.0f);

  inputManager->registerKey(GLFW_KEY_Q, KEY_QUIT);
  inputManager->registerKey(GLFW_KEY_W, KEY_FORWARD);
  inputManager->registerKey(GLFW_KEY_S, KEY_BACKWARD);
  inputManager->registerKey(GLFW_KEY_A, KEY_LEFT);
  inputManager->registerKey(GLFW_KEY_D, KEY_RIGHT);
  inputManager->registerKey(GLFW_KEY_1, KEY_SHADER1);
  inputManager->registerKey(GLFW_KEY_2, KEY_SHADER2);
  inputManager->registerKey(GLFW_KEY_3, KEY_SHADER3);
  inputManager->registerKey(GLFW_KEY_4, KEY_SHADER4);
  inputManager->registerKey(GLFW_KEY_SPACE, KEY_ACTION);
  inputManager->registerKey(GLFW_KEY_TAB, KEY_SWITCH);
  inputManager->init();
}

void MainSceneController::updateMode() {
  if (inputManager->isKeyPressed(KEY_SWITCH)) {
    switch (mode) {
    case ControllerMode::freeCamera:
      mode = ControllerMode::robotCamera;
      break;
    case ControllerMode::robotCamera:
      mode = ControllerMode::ballCamera;
      break;
    case ControllerMode::ballCamera:
      mode = ControllerMode::freeCamera;
      break;
    }
  }
}

void MainSceneController::updateFreeCameraMode(float dt) {
  if (mode != ControllerMode::freeCamera)
    return;

  double sensivity = 0.1;
  float cameraSpeed = 4.0f;

  double deltaX, deltaY;
  inputManager->getMouseDelta(deltaX, deltaY);
  deltaX *= sensivity;
  deltaY *= sensivity;

  freeCameraYaw += deltaX;
  freeCameraPitch -= deltaY;
  freeCameraPitch = std::min(freeCameraPitch, 89.0f);
  freeCameraPitch = std::max(freeCameraPitch, -89.0f);

  glm::vec3 dir;
  dir.x = cos(glm::radians(freeCameraYaw)) * cos(glm::radians(freeCameraPitch));
  dir.y = sin(glm::radians(freeCameraPitch));
  dir.z = sin(glm::radians(freeCameraYaw)) * cos(glm::radians(freeCameraPitch));

  dir = glm::normalize(dir);

  freeCamera.lookAt(freeCameraPos, freeCameraPos + dir,
                    glm::vec3(0.0f, 1.0f, 0.0f));

  if (inputManager->isKeyDown(KEY_FORWARD))
    freeCameraPos += dir * cameraSpeed * dt;
  if (inputManager->isKeyDown(KEY_BACKWARD))
    freeCameraPos -= dir * cameraSpeed * dt;
  if (inputManager->isKeyDown(KEY_LEFT)) {
    auto moveDir = glm::normalize(glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f)));
    freeCameraPos -= moveDir * cameraSpeed * dt;
  }
  if (inputManager->isKeyDown(KEY_RIGHT)) {
    auto moveDir = glm::normalize(glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f)));
    freeCameraPos += moveDir * cameraSpeed * dt;
  }
}

void MainSceneController::updateRobotCameraMode(float dt) {
  if (mode != ControllerMode::robotCamera)
    return;

  robotController->update(dt, *inputManager);
  robotController->updateEyeCamera(robotCamera);
}

void MainSceneController::updateBallCameraMode(float dt) {
  if (mode != ControllerMode::ballCamera)
    return;

  if (followedBall != nullptr) {
    auto ballPos = followedBall->getPosition();
    auto upVec = glm::vec3(1.0f, 0.0f, 0.0f);
    ballCamera.lookAt(ballCameraPos, ballPos, upVec);
  }
}
