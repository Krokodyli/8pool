#include "mainScene.h"
#include "../model/mesh/cuboidMeshGen.h"
#include "../model/mesh/sphereMeshGen.h"

MainScene::MainScene(int width, int height,
                     std::unique_ptr<InputManager> &inputManager)
    : camera(glm::radians(45.0f), (float)width / (float)height),
      inputManager(std::move(inputManager)), cameraPos(0.0f, 0.0f, -3.0f) {
  yaw = 90.f;
  pitch = 0.0f;
}

void MainScene::init() {
  registerKeys();

  renderer.setCamera(&camera);
  // shaders
  {
    std::vector<std::string> shaders = {"noshading", "gourand", "phong",
                                        "flat"};
    resourceManager.loadShaders(shaders);
    resourceManager.useShader(renderer, "phong");
  }
  // textures
  {
    std::vector<std::string> textures = {"sphere.png", "cube.png",
                                         "poolTable.png"};
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

    meshes["ball"] = ballMesh.getMesh();
    meshes["poolTable"] = tableMesh.getMesh();
    meshes["tableSide1"] = tableSide1.getMesh();
    meshes["tableSide2"] = tableSide2.getMesh();
    meshes["tableSide3"] = tableSide3.getMesh();
    meshes["tableLeg"] = tableLeg.getMesh();
  }
  resourceManager.addMeshes(meshes);

  Model fabricModel(resourceManager.getMeshID("poolTable"),
                   resourceManager.getTextureID("poolTable.png"),
                   ModelMaterials::fabric);

  Model ballModel(resourceManager.getMeshID("ball"),
                  resourceManager.getTextureID("sphere.png"),
                  ModelMaterials::plastic);

  Model lampModel(resourceManager.getMeshID("ball"),
                  glm::vec3(1.0f, 1.0f, 1.0f), ModelMaterials::plastic);

  Model tableSideXModel(resourceManager.getMeshID("tableSide1"),
                   glm::vec3(0.05f, 0.0f, 0.0f), ModelMaterials::blackPlastic);

  Model tableSideZModel(resourceManager.getMeshID("tableSide2"),
                   glm::vec3(0.05f, 0.0f, 0.0f), ModelMaterials::blackPlastic);

  Model tableSideYModel(resourceManager.getMeshID("tableSide3"),
                   glm::vec3(0.05f, 0.0f, 0.0f), ModelMaterials::blackPlastic);

  Model tableLegModel(resourceManager.getMeshID("tableLeg"),
                 glm::vec3(0.05f, 0.0f, 0.0f), ModelMaterials::blackPlastic);
  generateRoom();

  auto table = std::make_unique<PoolTable>(fabricModel, tableSideXModel,
                                           tableSideYModel, tableSideZModel,
                                           tableLegModel, glm::vec3(0.0f));
  gameObjects.push_back(std::move(table));
  // for (int i = 0; i < 4; i++) {
  //   float xPos = (tableWidth + borderThickness) / 2.0f;
  //   if (i % 2 == 1)
  //     xPos *= -1;
  //   float yPos = -tableHeight * 0.5f;
  //   float zPos = (tableLength + borderThickness) / 2.0f;

  //   if (i / 2 == 1)
  //     zPos *= -1;
  //   gameObjects.push_back(
  //       std::make_unique<Prop>(tableLeg, glm::vec3(xPos, yPos, zPos)));
  // }

  // gameObjects.push_back(std::make_unique<Prop>(
  //     tableSide1,
  //     glm::vec3(0.0f, 0.0f, (tableLength + borderThickness) * 0.5f)));
  // gameObjects.push_back(std::make_unique<Prop>(
  //     tableSide1,
  //     glm::vec3(0.0f, 0.0f, -(tableLength + borderThickness) * 0.5f)));

  // gameObjects.push_back(std::make_unique<Prop>(
  //     tableSide2,
  //     glm::vec3((tableWidth + borderThickness) * 0.5f, 0.0f, 0.0f)));
  // gameObjects.push_back(std::make_unique<Prop>(
  //     tableSide2,
  //     glm::vec3(-(tableWidth + borderThickness) * 0.5f, 0.0f, 0.0f)));

  // gameObjects.push_back(std::make_unique<Prop>(
  //     tableSide3, glm::vec3(0.0f, -borderThickness * 3.0f / 2.0f, 0.0f)));

  // PoolTable table(tableModel, glm::vec3(0.0f, -0.05f, 0.0f));
  srand(time(0));
  for (int i = 0; i < 10; i++) {
    auto pos = glm::vec3(0.0f, Ball::ballRadius, 0.0f);
    pos.x = (rand() % 100 / 100.0f) * PoolTable::width -
            PoolTable::width / 2.0f;
    pos.z = (rand() % 100 / 100.0f) * PoolTable::length -
            PoolTable::length / 2.0f;
    float xSpeed = (rand() % 5 - 2) * 0.2f;
    float zSpeed = (rand() % 5 - 2) * 0.2f;
    gameObjects.push_back(std::make_unique<Ball>(ballModel, pos));
    gameObjects[gameObjects.size() - 1]->setVelocity(
        glm::vec3(xSpeed, 0.0f, zSpeed));
  }
  auto mainLamp =
      std::make_unique<Lamp>(lampModel, glm::vec3(1.0f, 2.0f, 0.0f));
  lamp = mainLamp.get();
  gameObjects.push_back(std::move(mainLamp));
  gameObjects.push_back(
      std::make_unique<Lamp>(lampModel, glm::vec3(0.0, 2.0f, -0.5f)));
  gameObjects.push_back(
      std::make_unique<Lamp>(lampModel, glm::vec3(0.0, 2.0f, 0.5f)));
}

void MainScene::update(float dt) {
  processInput(dt);

  auto lampPos3 = lamp->getPosition();
  auto lampPos = glm::vec2(lampPos3.x, lampPos3.z);
  auto tangent = glm::vec2(lampPos.y, -lampPos.x);
  lamp->setVelocity(glm::vec3(tangent.x, 0.0f, tangent.y));

  for (auto &gameObject : gameObjects)
    gameObject->update(dt, *inputManager);
}

void MainScene::render() {
  renderer.prepareView();
  std::vector<Light *> lights;
  for (auto &gameObject : gameObjects) {
    auto modelLights = gameObject->getModelLights();
    for(auto light : modelLights)
      lights.push_back(light);
  }
  renderer.registerLights(lights);

  for (auto &gameObject : gameObjects)
    renderer.render(*gameObject, resourceManager);
}

void MainScene::processInput(float dt) {
  inputManager->update();

  if (inputManager->isKeyDown(KEY_FORWARD))
    cameraPos += cameraDirection * cameraSpeed * dt;
  else if (inputManager->isKeyDown(KEY_BACKWARD))
    cameraPos -= cameraDirection * cameraSpeed * dt;
  else if (inputManager->isKeyDown(KEY_LEFT))
    cameraPos -= glm::normalize(
                     glm::cross(cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f))) *
                 cameraSpeed * dt / 2.0f;
  else if (inputManager->isKeyDown(KEY_RIGHT))
    cameraPos += glm::normalize(
                     glm::cross(cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f))) *
                 cameraSpeed * dt / 2.0f;

  if (inputManager->isKeyPressed(KEY_SHADER1))
    resourceManager.useShader(renderer, "phong");
  else if (inputManager->isKeyPressed(KEY_SHADER2))
    resourceManager.useShader(renderer, "gourand");
  else if (inputManager->isKeyPressed(KEY_SHADER3))
    resourceManager.useShader(renderer, "flat");
  else if (inputManager->isKeyPressed(KEY_SHADER4))
    resourceManager.useShader(renderer, "noshading");

  double sensivity = 0.1;
  double deltaX;
  double deltaY;
  inputManager->getMouseDelta(deltaX, deltaY);
  deltaX *= sensivity;
  deltaY *= -sensivity;

  yaw += deltaX;
  pitch += deltaY;
  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;

  cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraDirection.y = sin(glm::radians(pitch));
  cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraDirection = glm::normalize(cameraDirection);

  camera.lookAt(cameraPos, cameraPos + cameraDirection,
                glm::vec3(0.0f, 1.0f, 0.0f));
}

void MainScene::registerKeys() {
  inputManager->registerKey(GLFW_KEY_Q, KEY_QUIT);
  inputManager->registerKey(GLFW_KEY_W, KEY_FORWARD);
  inputManager->registerKey(GLFW_KEY_S, KEY_BACKWARD);
  inputManager->registerKey(GLFW_KEY_A, KEY_LEFT);
  inputManager->registerKey(GLFW_KEY_D, KEY_RIGHT);
  inputManager->registerKey(GLFW_KEY_1, KEY_SHADER1);
  inputManager->registerKey(GLFW_KEY_2, KEY_SHADER2);
  inputManager->registerKey(GLFW_KEY_3, KEY_SHADER3);
  inputManager->registerKey(GLFW_KEY_4, KEY_SHADER4);
  inputManager->init();
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
