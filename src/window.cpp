#include "window.h"
#include "ball.h"
#include "filesystemHelper.h"
#include "poolTable.h"

Window::Window(int width, int height, std::string title)
    : width(width), height(height), title(title),
      camera(glm::radians(45.0f), (float)width / (float)height),
      cameraPos(0.0f, 0.0f, -3.0f), cameraDirection(0.0f, 1.0f, 0.0f) {
  yaw = 90.0f;
  pitch = 0.0f;
}

void Window::init() {
  createWindow();
  loadGlad();
  setUpOpenGL();
  setUpGLFW();
}

void Window::runLoop() {
  // load and init
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

  // key bindings
  registerKeys();

  PoolTable table(resourceManager, glm::vec3(0.0f, -0.05f, 0.0f));
  std::vector<Ball> balls;
  srand(time(0));
  for (int i = 0; i < 10; i++) {
    auto pos = glm::vec3(0.0f, Ball::ballRadius, 0.0f);
    pos.x = (rand() % 100 / 100.0f) * PoolTable::poolTableWidth -
      PoolTable::poolTableWidth / 2.0f;
    pos.z = (rand() % 100 / 100.0f) * PoolTable::poolTableLength -
      PoolTable::poolTableLength / 2.0f;
    float xSpeed = (rand()% 5 - 2) * 0.2f;
    float zSpeed = (rand() % 5 - 2) * 0.2f;
    balls.push_back(Ball(resourceManager, pos));
    balls[balls.size() - 1].setVelocity(glm::vec3(xSpeed, 0.0f, zSpeed));
  }

  float lastTime;
  float time = glfwGetTime();
  int frames = 0;
  while (!glfwWindowShouldClose(glWindow)) {
    frames++;
    lastTime = time;
    time = glfwGetTime();
    float dt = time - lastTime;

    inputManager.update(glWindow);
    processInput(dt);

    for (auto &ball : balls)
      ball.update(dt);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto &ball : balls)
      renderer.render(ball, resourceManager);
    renderer.render(table, resourceManager);

    glfwSwapBuffers(glWindow);
    glfwPollEvents();
  }
  std::cout << (float)frames / glfwGetTime() << std::endl;
}

void Window::createWindow() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  glWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (glWindow == NULL) {
    throw std::runtime_error("Could not create a window");
  }

  glfwMakeContextCurrent(glWindow);

  glfwSetFramebufferSizeCallback(
      glWindow, [](GLFWwindow *window, int newWidth, int newHeight) {
        glViewport(0, 0, newWidth, newHeight);
      });
}

void Window::loadGlad() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("Could not load GLAD");
}

void Window::setUpOpenGL() {
  glEnable(GL_DEPTH_TEST);
  glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
}

void Window::setUpGLFW() {
  glfwSetInputMode(glWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::registerKeys() {
  inputManager.registerKey(GLFW_KEY_Q, KEY_QUIT);
  inputManager.registerKey(GLFW_KEY_W, KEY_FORWARD);
  inputManager.registerKey(GLFW_KEY_S, KEY_BACKWARD);
  inputManager.registerKey(GLFW_KEY_A, KEY_LEFT);
  inputManager.registerKey(GLFW_KEY_D, KEY_RIGHT);
  inputManager.registerKey(GLFW_KEY_SPACE, KEY_ACTION1);
  inputManager.registerKey(GLFW_KEY_F, KEY_ACTION2);
  inputManager.registerKey(GLFW_KEY_E, KEY_ACTION3);
  inputManager.init(glWindow);
}

void Window::processInput(float dt) {
  if (inputManager.isKeyPressed(KEY_QUIT))
    glfwSetWindowShouldClose(glWindow, GLFW_TRUE);
  if (inputManager.isKeyDown(KEY_FORWARD))
    cameraPos += cameraDirection * cameraSpeed * dt;
  else if (inputManager.isKeyDown(KEY_BACKWARD))
    cameraPos -= cameraDirection * cameraSpeed * dt;
  else if (inputManager.isKeyDown(KEY_LEFT))
    cameraPos -= glm::normalize(
                     glm::cross(cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f))) *
                 cameraSpeed * dt / 2.0f;
  else if (inputManager.isKeyDown(KEY_RIGHT))
    cameraPos += glm::normalize(
                     glm::cross(cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f))) *
                 cameraSpeed * dt / 2.0f;

  if (inputManager.isKeyPressed(KEY_ACTION2))
    resourceManager.toggleShader(renderer);

  if (inputManager.isKeyPressed(KEY_ACTION1))
    isMoving = !isMoving;

  double sensivity = 0.1;
  double deltaX;
  double deltaY;
  inputManager.getMouseDelta(deltaX, deltaY);
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
