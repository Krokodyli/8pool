#include "window.h"
#include "filesystemHelper.h"

Window::Window(int width, int height, std::string title)
    : width(width), height(height), title(title),
      camera(glm::radians(45.0f), (float)width/(float)height),
      cameraPos(0.0f, 0.0f, -3.0f), cameraDirection(0.0f, 1.0f, 0.0f){
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
  shaderManager.load({"basic","basic2"}, renderer);

  float cubeModelData[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

  std::vector<float> vertices, normals;
  for(int i = 0; i < sizeof(cubeModelData)/sizeof(float); i++) {
    if((i%6) < 3)
      vertices.push_back(cubeModelData[i]);
    else
      normals.push_back(cubeModelData[i]);
  }

  glm::mat4 cubes[4] = {
    glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.0f, 0.0f)),
    glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 0.0f)),
    glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 0.0f)),
    glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f))
  };

  Model model(vertices, normals);

  float lastTime;
  float time = glfwGetTime();
  int frames = 0;
  while(!glfwWindowShouldClose(glWindow)) {
    frames++;
    lastTime = time;
    float time = glfwGetTime();
    float dt = lastTime - time;

    processInput(dt);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i = 0; i < 4; i++ ) {
      if(isMoving)
        cubes[i] = glm::rotate(cubes[i], glm::radians((float)i*5.0f / 3.0f), glm::vec3(1.0f, 1.0f, 0.0f));
      renderer.render(&model, cubes[i]);
    }

    renderer.renderLight(&model);

    glfwSwapBuffers(glWindow);
    glfwPollEvents();
  }
  std::cout << (float)frames/glfwGetTime() << std::endl;
}

void Window::createWindow() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  glWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if(glWindow == NULL) {
    throw std::runtime_error("Could not create a window");
  }

  glfwMakeContextCurrent(glWindow);

  glfwSetFramebufferSizeCallback(glWindow,
    [](GLFWwindow *window, int newWidth, int newHeight) {
      glViewport(0, 0, newWidth, newHeight);
  });
}

void Window::loadGlad() {
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("Could not load GLAD");
}

void Window::setUpOpenGL() {
  glEnable(GL_DEPTH_TEST);
}

void Window::setUpGLFW() {
  glfwSetInputMode(glWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::processInput(float dt) {
  if(glfwGetKey(glWindow, GLFW_KEY_Q) == GLFW_PRESS)
    glfwSetWindowShouldClose(glWindow, GLFW_TRUE);
  if(glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS)
    cameraPos -= cameraDirection * cameraSpeed * dt;
  else if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS)
    cameraPos += cameraDirection * cameraSpeed * dt;
  else if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS)
    cameraPos += glm::normalize(glm::cross(cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed * dt / 2.0f;
  else if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS)
    cameraPos -= glm::normalize(
                     glm::cross(cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f))) *
      cameraSpeed * dt / 2.0f;

  if(glfwGetKey(glWindow, GLFW_KEY_F) == GLFW_PRESS)
    shaderManager.toggleShader(renderer);

  if(glfwGetKey(glWindow, GLFW_KEY_SPACE)) {
    if(!wasPressed) {
      isMoving = !isMoving;
      wasPressed = true;
    }
  } else {
    wasPressed = false;
  }
  double newMouseX, newMouseY;
  glfwGetCursorPos(glWindow, &newMouseX, &newMouseY);

  float sensivity = 0.05f;
  float deltaX = (newMouseX - mouseX) * sensivity;
  float deltaY = -(newMouseY - mouseY) * sensivity;

  yaw += deltaX;
  pitch += deltaY;
  if(pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;

  cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraDirection.y = sin(glm::radians(pitch));
  cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraDirection = glm::normalize(cameraDirection);

  mouseX = newMouseX;
  mouseY = newMouseY;

  camera.lookAt(cameraPos, cameraPos+cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f));
}
