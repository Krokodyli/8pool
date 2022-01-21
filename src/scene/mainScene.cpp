#include "mainScene.h"

MainScene::MainScene(int width, int height,
                     std::unique_ptr<InputManager> &inputManager)
    : controller(std::move(inputManager), (float)width / (float)height) { }

void MainScene::init()
{
  MainSceneLoader loader(gameObjects, resourceManager);
  loader.loadResources();
  resourceManager.useShader(renderer, "blinn");

  robot = loader.generateRobot();
  controller.setRobot(robot);

  std::vector<Lamp *> lamps;
  loader.generateLamps(lamps);
  movingLamp = lamps[1];
  movingLamp->setPosition(glm::vec3(0.0f, 0.9f, 1.1f));
  controller.setLamps(lamps);

  loader.generatePoolTable();

  std::vector<Ball *> balls;
  loader.generateBalls(balls);
  controller.setBalls(balls);
  controller.setFollowedBall(balls[0]);

  loader.generateRoom();
}

void MainScene::update(float dt)
{
  controller.update(dt);
  controller.updateRenderer(dt, renderer, resourceManager);

  moveLamp();

  for (auto &gameObject : gameObjects)
    gameObject->update(dt);
}

void MainScene::render()
{
  renderer.setCamera(controller.getCurrentCamera());

  renderer.prepareView();
  std::vector<Light *> lights;
  for (auto &gameObject : gameObjects)
  {
    auto modelLights = gameObject->getModelLights();
    for (auto light : modelLights)
      lights.push_back(light);
  }
  renderer.registerLights(lights);

  for (auto &gameObject : gameObjects)
    renderer.render(*gameObject, resourceManager);
}

bool MainScene::shouldClose() {
  return controller.shouldClose();
}

void MainScene::moveLamp()
{
  auto lampPos = glm::vec2(movingLamp->getPosition().x,
                           movingLamp->getPosition().z);
  movingLamp->setVelocity(glm::vec3(-lampPos.y, 0.0f, lampPos.x));
  movingLamp->setVelocity(glm::vec3(0.0f));
}
