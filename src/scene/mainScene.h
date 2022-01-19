#pragma once

#include "../camera.h"
#include "../game/object/ball.h"
#include "../game/object/lamp.h"
#include "../game/object/poolTable.h"
#include "../game/object/prop.h"
#include "../keys.h"
#include "../renderer.h"
#include "../resourceManager/resourceManager.h"
#include "mainSceneController.h"
#include "scene.h"

class MainScene : public Scene {
private:
  ResourceManager resourceManager;
  Renderer renderer;
  MainSceneController controller;

  Lamp *lamps[3];

  std::vector<std::unique_ptr<GameObject>> gameObjects;

  void generateRoom();
  void updateLamp();
public:
  MainScene(int width, int height, std::unique_ptr<InputManager> &inputManager);

  virtual void init();
  virtual void update(float dt);
  virtual void render();
};
