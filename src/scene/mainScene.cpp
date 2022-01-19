#include "mainScene.h"
#include "../game/object/robot.h"
#include "../model/mesh/cuboidMeshGen.h"
#include "../model/mesh/sphereMeshGen.h"

MainScene::MainScene(int width, int height,
                     std::unique_ptr<InputManager> &inputManager)
  : controller(std::move(inputManager), (float)width/(float)height) { }

void MainScene::init() {
  // textures
  {
    std::vector<std::string> textures = {"sphere.png", "cube.png",
                                         "poolTable.png", "robot.png"};
    resourceManager.loadTextures(textures);
  }
  // meshes

  float borderThickness = 0.05f;
  float tableWidth = PoolTable::width;
  float tableLength = PoolTable::length;
  float fabricThickness = 0.05f;
  float borderHeight = fabricThickness * 2 + 0.05f;
  float tableLegSize = 0.04f;
  float tableHeight = 0.787f;
  std::unordered_map<std::string, std::unique_ptr<Mesh>> meshes;
  {
    CuboidMeshGenerator tableMesh(tableWidth, fabricThickness, tableLength);
    CuboidMeshGenerator tableSide1(tableWidth + borderThickness * 2.0f,
                                   borderHeight, borderThickness);
    CuboidMeshGenerator tableSide2(borderThickness, borderHeight, tableLength);
    CuboidMeshGenerator tableSide3(tableWidth + borderThickness * 2.0f,
                                   borderThickness,
                                   tableLength + borderThickness * 2);
    CuboidMeshGenerator tableLeg(tableLegSize, tableHeight, tableLegSize);

    SphereMeshGenerator ballMesh(0.0285f, 4);

    CuboidMeshGenerator robotHead(Robot::headSize, Robot::headSize,
                                  Robot::headSize);
    CuboidMeshGenerator robotNose(Robot::noseThickness, Robot::noseThickness,
                                  Robot::noseLength);

    meshes["robotHead"] = robotHead.getMesh();
    meshes["robotNose"] = robotNose.getMesh();
    meshes["ball"] = ballMesh.getMesh();
    meshes["poolTable"] = tableMesh.getMesh();
    meshes["tableSide1"] = tableSide1.getMesh();
    meshes["tableSide2"] = tableSide2.getMesh();
    meshes["tableSide3"] = tableSide3.getMesh();
    meshes["tableLeg"] = tableLeg.getMesh();
  }
  resourceManager.addMeshes(meshes);

  Model robotHeadModel(resourceManager.getMeshID("robotHead"),
                       resourceManager.getTextureID("robot.png"),
                       ModelMaterials::plastic);

  Model robotNoseModel(resourceManager.getMeshID("robotNose"),
                       glm::vec3(0.0f, 0.0f, 0.0f), ModelMaterials::plastic);

  auto robot = std::make_unique<Robot>(robotHeadModel, robotNoseModel,
                                       glm::vec3(3.0f, 1.0f, 0.0f));
  controller.setRobot(robot.get());
  gameObjects.push_back(std::move(robot));

  Model fabricModel(resourceManager.getMeshID("poolTable"),
                    resourceManager.getTextureID("poolTable.png"),
                    ModelMaterials::fabric);

  Model ballModel(resourceManager.getMeshID("ball"),
                  resourceManager.getTextureID("sphere.png"),
                  ModelMaterials::plastic);

  Model lampModel(resourceManager.getMeshID("ball"),
                  glm::vec3(1.0f, 1.0f, 1.0f), ModelMaterials::plastic);

  Model tableSideXModel(resourceManager.getMeshID("tableSide1"),
                        glm::vec3(0.05f, 0.0f, 0.0f),
                        ModelMaterials::blackPlastic);

  Model tableSideZModel(resourceManager.getMeshID("tableSide2"),
                        glm::vec3(0.05f, 0.0f, 0.0f),
                        ModelMaterials::blackPlastic);

  Model tableSideYModel(resourceManager.getMeshID("tableSide3"),
                        glm::vec3(0.05f, 0.0f, 0.0f),
                        ModelMaterials::blackPlastic);

  Model tableLegModel(resourceManager.getMeshID("tableLeg"),
                      glm::vec3(0.05f, 0.0f, 0.0f),
                      ModelMaterials::blackPlastic);
  generateRoom();

  auto table = std::make_unique<PoolTable>(fabricModel, tableSideXModel,
                                           tableSideYModel, tableSideZModel,
                                           tableLegModel, glm::vec3(0.0f));
  gameObjects.push_back(std::move(table));

  srand(time(0));
  for (int i = 0; i < 10; i++) {
    auto pos = glm::vec3(0.0f, Ball::ballRadius, 0.0f);
    pos.x =
        (rand() % 100 / 100.0f) * PoolTable::width - PoolTable::width / 2.0f;
    pos.z =
        (rand() % 100 / 100.0f) * PoolTable::length - PoolTable::length / 2.0f;
    float xSpeed = (rand() % 3 + 1) * 0.2f * (rand()%2 == 0 ? 1 : -1);
    float zSpeed = (rand() % 3 + 1) * 0.2f * (rand() % 2 == 0 ? 1 : -1);
    auto ball = std::make_unique<Ball>(ballModel, pos);
    if(i == 0)
      controller.setFollowedBall(ball.get());
    ball->setVelocity(glm::vec3(xSpeed, 0.0f, zSpeed));
    gameObjects.push_back(std::move(ball));
  }

  for(int i = 0; i < 3; i++) {
    auto lamp = std::make_unique<Lamp>(lampModel, glm::vec3((i-1)*4.0f, 2.0f, 0.0f));
    lamps[i] = lamp.get();
    gameObjects.push_back(std::move(lamp));
  }
}

void MainScene::update(float dt) {
  controller.update(dt);

  updateLamp();

  for (auto &gameObject : gameObjects)
    gameObject->update(dt);
}

void MainScene::render() {
  renderer.setCamera(controller.getCurrentCamera());
  renderer.prepareView();
  std::vector<Light *> lights;
  for (auto &gameObject : gameObjects) {
    auto modelLights = gameObject->getModelLights();
    for (auto light : modelLights)
      lights.push_back(light);
  }
  renderer.registerLights(lights);

  for (auto &gameObject : gameObjects)
    renderer.render(*gameObject, resourceManager);
}

void MainScene::generateRoom() {
  auto roomSize = glm::vec3(10.f, 4.0f, 10.f);
  auto tableHeight = 0.787f;
  std::unordered_map<std::string, std::unique_ptr<Mesh>> meshes;
  auto color = glm::vec3(0.9f, 0.9f, 0.9f);
  auto material = ModelMaterials::plastic;
  float thickness = 0.01f;
  {
    CuboidMeshGenerator floor(roomSize.x, thickness, roomSize.z);
    CuboidMeshGenerator wallX(roomSize.x, roomSize.y, thickness);
    CuboidMeshGenerator wallZ(thickness, roomSize.y, roomSize.z);
    meshes["floor"] = floor.getMesh();
    meshes["wallX"] = wallX.getMesh();
    meshes["wallZ"] = wallZ.getMesh();
  }
  resourceManager.addMeshes(meshes);
  Model floorM(resourceManager.getMeshID("floor"), color, material);
  Model wallXM(resourceManager.getMeshID("wallX"), color, material);
  Model wallZM(resourceManager.getMeshID("wallZ"), color, material);

  gameObjects.push_back(std::make_unique<Prop>(
      floorM, glm::vec3(0.0f, -tableHeight - thickness / 2.0f, 0.0f)));
  gameObjects.push_back(std::make_unique<Prop>(
      floorM,
      glm::vec3(0.0f, roomSize.y - tableHeight + thickness / 2.0f, 0.0f)));

  float wallYPos = roomSize.y / 2.0f - tableHeight;
  gameObjects.push_back(std::make_unique<Prop>(
      wallZM, glm::vec3(-roomSize.x / 2.0f, wallYPos, 0.0f)));
  gameObjects.push_back(std::make_unique<Prop>(
      wallZM, glm::vec3(roomSize.x / 2.0f, wallYPos, 0.0f)));

  gameObjects.push_back(std::make_unique<Prop>(
      wallXM, glm::vec3(0.0f, wallYPos, -roomSize.z / 2.0f)));
  gameObjects.push_back(std::make_unique<Prop>(
      wallXM, glm::vec3(0.0f, wallYPos, roomSize.z / 2.0f)));
}

void MainScene::updateLamp() {
  auto lampPos3 = lamps[1]->getPosition();
  auto lampPos = glm::vec2(lampPos3.x, lampPos3.z);
  auto tangent = glm::vec2(lampPos.y, -lampPos.x);
  lamps[1]->setVelocity(glm::vec3(tangent.x, 0.0f, tangent.y));
}
