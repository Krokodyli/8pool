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
    std::vector<std::string> shaders = {"basic", "basic2"};
    resourceManager.loadShaders(shaders);
    resourceManager.useShader(renderer, "basic2");
  }
  // textures
  {
    std::vector<std::string> textures = {"sphere.png", "cube.png",
                                         "poolTable.png"};
    resourceManager.loadTextures(textures);
  }
  // meshes
  std::unordered_map<std::string, std::unique_ptr<Mesh>> meshes;
  {
    CuboidMeshGenerator cubeMesh;
    CuboidMeshGenerator tableMesh(1.12f, 0.10f, 2.24f);
    SphereMeshGenerator ballMesh(0.0285f, 4);

    meshes["ball"] = ballMesh.getMesh();
    meshes["poolTable"] = tableMesh.getMesh();
    meshes["cube"] = cubeMesh.getMesh();
  }
  resourceManager.addMeshes(meshes);

  Model tableModel(resourceManager.getMeshID("poolTable"),
                   resourceManager.getTextureID("poolTable.png"),
                   ModelMaterials::gold);

  Model ballModel(resourceManager.getMeshID("ball"),
                  resourceManager.getTextureID("sphere.png"),
                  ModelMaterials::gold);

  PoolTable table(tableModel, glm::vec3(0.0f, -0.05f, 0.0f));
  srand(time(0));
  for (int i = 0; i < 10; i++) {
    auto pos = glm::vec3(0.0f, Ball::ballRadius, 0.0f);
    pos.x = (rand() % 100 / 100.0f) * PoolTable::poolTableWidth -
            PoolTable::poolTableWidth / 2.0f;
    pos.z = (rand() % 100 / 100.0f) * PoolTable::poolTableLength -
            PoolTable::poolTableLength / 2.0f;
    float xSpeed = (rand() % 5 - 2) * 0.2f;
    float zSpeed = (rand() % 5 - 2) * 0.2f;
    gameObjects.push_back(std::make_unique<Ball>(ballModel, pos));
    gameObjects[gameObjects.size() - 1]->setVelocity(
        glm::vec3(xSpeed, 0.0f, zSpeed));
  }
  gameObjects.push_back(std::make_unique<PoolTable>(tableModel, glm::vec3(0.0f, -0.05f, 0.0f)));
}

void MainScene::update(float dt) {
  processInput(dt);
  for (auto &gameObject : gameObjects)
    gameObject->update(dt, *inputManager);
}

void MainScene::render() {
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

  if (inputManager->isKeyPressed(KEY_ACTION2))
    resourceManager.toggleShader(renderer);

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
  inputManager->registerKey(GLFW_KEY_SPACE, KEY_ACTION1);
  inputManager->registerKey(GLFW_KEY_F, KEY_ACTION2);
  inputManager->registerKey(GLFW_KEY_E, KEY_ACTION3);
  inputManager->init();
}
