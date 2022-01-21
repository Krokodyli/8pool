#pragma once

#include "../game/object/ball.h"
#include "../game/object/lamp.h"
#include "../game/object/multipartGameObject.h"
#include "../game/object/poolTable.h"
#include "../game/object/robot.h"
#include "../model/mesh/cuboidMeshGen.h"
#include "../model/mesh/sphereMeshGen.h"
#include "../renderer/camera.h"
#include "../renderer/renderer.h"
#include "../resourceManager/resourceManager.h"
#include "../scene/keys.h"
#include "mainSceneController.h"
#include "mainSceneLoader.h"
#include "scene.h"

class MainScene : public Scene {
private:
  ResourceManager resourceManager;
  Renderer renderer;
  MainSceneController controller;

  Robot *robot;
  Lamp *movingLamp;

  std::vector<std::unique_ptr<GameObject>> gameObjects;

  void moveLamp();
public:
  MainScene(int width, int height, std::unique_ptr<InputManager> &inputManager);

  virtual void init();
  virtual void update(float dt);
  virtual void render();
  virtual bool shouldClose();
};
