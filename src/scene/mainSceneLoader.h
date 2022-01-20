#pragma once

#include "../game/object/robot.h"
#include "../model/mesh/cuboidMeshGen.h"
#include "../model/mesh/sphereMeshGen.h"
#include "../resourceManager/resourceManager.h"
#include "../game/object/lamp.h"
#include "../game/object/ball.h"
#include "../game/object/poolTable.h"

class MainSceneLoader {
private:
  std::vector<std::unique_ptr<GameObject>> &gameObjects;
  ResourceManager &resourceManager;

  void loadShaders();
  void generateMeshes();
  void loadTextures();
public:
  MainSceneLoader(std::vector<std::unique_ptr<GameObject>> &gameObjects,
                  ResourceManager &resourceManager);

  Robot *generateRobot();
  void generateLamps(std::vector<Lamp*> &lamps);
  PoolTable *generatePoolTable();
  void generateBalls(std::vector<Ball*> &balls);
  void generateRoom();

  void loadResources();
};
