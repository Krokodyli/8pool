#include "window.h"
#include "glm/detail/func_trigonometric.hpp"
#include "glm/detail/type_vec.hpp"
#include "glm/gtc/quaternion.hpp"
#include "model.h"
#include "shader.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Window::Window(int width, int height, std::string title)
    : width(width), height(height), title(title),
      camera(glm::radians(45.0f), (float)width/(float)height),
      cameraPos(0.0f, 0.0f, -3.0f), cameraDirection(0.0f, 1.0f, 0.0f){
  yaw = 90.0f;
  pitch = 0.0f;
}

Window::~Window() {
  glfwTerminate();
}

void Window::init() {
  initGLFW();
  createWindow();
  loadGlad();
  setUpOpenGL();
  setUpGLFW();
}

void Window::runLoop() {
  renderer.setCamera(&camera);
  if(!shader.load("tmpshader1.vshad", "tmpshader1.fshad")) {
    std::cout << "Could not load shaders\n";
    std::cout << shader.getError() << "\n";
    return;
  }
  renderer.setShader(&shader);

  std::vector<float> vertices = {
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     -0.5f, -0.5f,  0.5f,
     -0.5f, -0.5f, -0.5f,

     -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f, -0.5f,
  };

  glm::mat4 cubes[4] = {
    glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.0f, 0.0f)),
    glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 0.0f)),
    glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 0.0f)),
    glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f))
  };

  Model model(vertices);

  float lastTime;
  float time = glfwGetTime();
  int frames;
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
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(glWindow);
    glfwPollEvents();
  }
  std::cout << (float)frames/glfwGetTime() << std::endl;
}

void Window::initGLFW() {
  if(!glfwInit())
    throw std::runtime_error("Could not init GLFW");
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
