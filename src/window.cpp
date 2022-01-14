#include "window.h"
#include "filesystemHelper.h"

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
  renderer.setCamera(&camera);
  shaderManager.load({"basic", "basic2"}, renderer);
  registerKeys();

  constexpr int cubesCount = 16;
  glm::mat4 cubes[cubesCount] = {
      glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f)),

      glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(12.0f, 1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(14.0f, 1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(16.0f, 1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(24.0f, 1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(18.0f, 1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 1.0f, 0.0f)),
      glm::translate(glm::mat4(1.0f), glm::vec3(22.0f, 1.0f, 0.0f))};

  // for(int i = 0; i < cubesCount; i++) {
  //   cubes[i] = glm::scale(cubes[i], glm::vec3(0.0572, 0.0572, 0.0572));
  // }
   CuboidMesh cubeMesh(1.0f, 1.0f, 1.0f);
   Model model = cubeMesh.generateModel();
  // auto start = std::chrono::high_resolution_clock::now();
  // SphereMesh sphereMesh(1.0f, 5);
  // auto stop = std::chrono::high_resolution_clock::now();
  // double duration =
  //     std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
  //         .count();
  // Logger::log("Mesh generation duration: " +
  //             std::to_string(duration / 1000000.0));
  // Model model = sphereMesh.generateModel();
  // Logger::log("Model triangle count: " +
  //             std::to_string(model.getTriangleCount()));
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < cubesCount; i++) {
      if (isMoving)
        cubes[i] = glm::rotate(cubes[i], glm::radians((float)i * 5.0f / 3.0f),
                               glm::vec3(1.0f, 1.0f, 0.0f));
      renderer.render(model, cubes[i]);
    }

    renderer.renderLight(model);

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

void Window::setUpOpenGL() { glEnable(GL_DEPTH_TEST); }

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
    shaderManager.toggleShader(renderer);

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
