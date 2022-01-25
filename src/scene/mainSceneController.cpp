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

  ballController.update(dt, *inputManager);

  for (auto &lampController : lampControllers)
    lampController->update(dt, *inputManager);

  if (inputManager->isKeyPressed(KEY_QUIT))
    shouldCloseFlag = true;
}

void MainSceneController::updateRenderer(float dt, Renderer &renderer,
                                         ResourceManager &resourceManager) {
  float sensivity = 0.01f;
  double deltaY, deltaX;
  inputManager->getScrollDelta(deltaX, deltaY);
  inputManager->resetScrollDelta();
  deltaY *= sensivity;
  renderer.setFogFactor(renderer.getFogFactor() + deltaY);

  if (inputManager->isKeyPressed(KEY_SHADER1))
    resourceManager.useShader(renderer, "blinn");
  else if (inputManager->isKeyPressed(KEY_SHADER2))
    resourceManager.useShader(renderer, "phong");
  else if (inputManager->isKeyPressed(KEY_SHADER3))
    resourceManager.useShader(renderer, "gourand");
  else if (inputManager->isKeyPressed(KEY_SHADER4))
    resourceManager.useShader(renderer, "flat");
  else if (inputManager->isKeyPressed(KEY_SHADER5))
    resourceManager.useShader(renderer, "noshading");
}

ControllerMode MainSceneController::getCurrentMode() { return mode; }

InputManager *MainSceneController::getInputManager() {
  return inputManager.get();
}

void MainSceneController::setFollowedBall(Ball *ball) { followedBall = ball; }

void MainSceneController::setRobot(Robot *robot) {
  robot->setController(&robotController);
}

void MainSceneController::setBalls(std::vector<Ball *> &balls) {
  for (auto ball : balls)
    ball->setController(&ballController);
}

void MainSceneController::setLamps(std::vector<Lamp *> &lamps) {
  auto lamp1Controller = std::make_unique<LampController>(KEY_LIGHT1_TOGGLE);
  auto lamp2Controller = std::make_unique<LampController>(
                                                          KEY_LIGHT2_TOGGLE, 1.0f, 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
  auto lamp3Controller = std::make_unique<LampController>(KEY_LIGHT3_TOGGLE);
  lamps[0]->setController(lamp1Controller.get());
  lamps[1]->setPosition(glm::vec3(0.0f, 1.1f, 0.0f));
  lamps[1]->setController(lamp2Controller.get());
  lamps[2]->setController(lamp3Controller.get());
  lampControllers.push_back(std::move(lamp1Controller));
  lampControllers.push_back(std::move(lamp2Controller));
  lampControllers.push_back(std::move(lamp3Controller));
}

bool MainSceneController::shouldClose() { return shouldCloseFlag; }

void MainSceneController::init() {
  mode = ControllerMode::freeCamera;

  freeCameraPos = glm::vec3(0.0f, 1.0f, -2.0f);
  freeCameraPitch = -30.0f;
  freeCameraYaw = 90.0f;

  ballCameraPos = glm::vec3(-1.0f, 2.0f, 0.0f);

  std::unordered_map<int, int> keysToRegister{
      {GLFW_KEY_Q, KEY_QUIT},          {GLFW_KEY_W, KEY_FORWARD},
      {GLFW_KEY_S, KEY_BACKWARD},      {GLFW_KEY_A, KEY_LEFT},
      {GLFW_KEY_D, KEY_RIGHT},         {GLFW_KEY_1, KEY_SHADER1},
      {GLFW_KEY_2, KEY_SHADER2},       {GLFW_KEY_3, KEY_SHADER3},
      {GLFW_KEY_4, KEY_SHADER4},       {GLFW_KEY_5, KEY_SHADER5},
      {GLFW_KEY_SPACE, KEY_ACTION},    {GLFW_KEY_TAB, KEY_SWITCH},
      {GLFW_KEY_F, KEY_MOVE_TOGGLE},   {GLFW_KEY_7, KEY_LIGHT1_TOGGLE},
      {GLFW_KEY_8, KEY_LIGHT2_TOGGLE}, {GLFW_KEY_9, KEY_LIGHT3_TOGGLE}
  };

  for (auto &entry : keysToRegister)
    inputManager->registerKey(entry.first, entry.second);

  inputManager->init();
}

void MainSceneController::updateMode() {
  if (inputManager->isKeyPressed(KEY_SWITCH)) {
    unsigned int uintMode = (unsigned int)mode;
    uintMode = (uintMode + 1) % 3;
    mode = (ControllerMode)uintMode;
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

  robotController.update(dt, *inputManager);
  robotController.updateEyeCamera(robotCamera);
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
