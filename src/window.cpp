#include "window.h"

Window::Window(int width, int height, std::string title)
  : width(width), height(height), title(title) { }

void Window::init() {
  createWindow();
  loadGlad();
  setUpOpenGL();
  setUpGLFW();
}

void Window::runLoop() {
  auto inputManager = std::make_unique<InputManager>(glWindow);
  auto scene = std::make_unique<MainScene>(width, height, inputManager);

  scene->init();

  float lastTime;
  float time = glfwGetTime();

  while (!glfwWindowShouldClose(glWindow) && !scene->shouldClose()) {
    lastTime = time;
    time = glfwGetTime();
    float dt = time - lastTime;

    scene->update(dt);

    glClearColor(0.3176f, 0.4431f, 0.8196f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->render();

    glfwSwapBuffers(glWindow);
    glfwPollEvents();
  }
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
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

void Window::setUpGLFW() {
  glfwSetInputMode(glWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
