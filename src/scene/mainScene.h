#pragma once

#include "../camera.h"
#include "../game/object/ball.h"
#include "../game/object/poolTable.h"
#include "../game/object/lamp.h"
#include "../keys.h"
#include "../renderer.h"
#include "../resourceManager/resourceManager.h"
#include "scene.h"

class MainScene : public Scene {
private:
  ResourceManager resourceManager;
  Camera camera;
  Renderer renderer;
  std::unique_ptr<InputManager> inputManager;

  float yaw, pitch;
  float cameraSpeed = 6.00f;
  glm::vec3 cameraPos;
  glm::vec3 cameraDirection;

  std::vector<std::unique_ptr<GameObject>> gameObjects;

  void registerKeys();
  void processInput(float dt);

public:
  MainScene(int width, int height, std::unique_ptr<InputManager> &inputManager);

  virtual void init();
  virtual void update(float dt);
  virtual void render();
};
