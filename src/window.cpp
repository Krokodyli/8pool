#include "window.h"
#include "glm/detail/func_trigonometric.hpp"
#include "glm/detail/type_vec.hpp"
#include "glm/gtc/quaternion.hpp"
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
  Shader shader;
  if(!shader.load("tmpshader1.vshad", "tmpshader1.fshad")) {
    std::cout << "Could not load shaders\n";
    std::cout << shader.getError() << "\n";
    return;
  }

  float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.2f,
    0.5f, -0.5f, -0.5f, 0.2f,
    0.5f,  0.5f, -0.5f, 0.2f,
    0.5f,  0.5f, -0.5f, 0.2f,
    -0.5f,  0.5f, -0.5f, 0.2f,
    -0.5f, -0.5f, -0.5f, 0.2f,

    -0.5f, -0.5f,  0.5f, 0.4f,
    0.5f, -0.5f,  0.5f, 0.4f,
    0.5f,  0.5f,  0.5f, 0.4f,
    0.5f,  0.5f,  0.5f, 0.4f,
    -0.5f,  0.5f,  0.5f, 0.4f,
    -0.5f, -0.5f,  0.5f, 0.4f,

    -0.5f,  0.5f,  0.5f, 0.6f,
    -0.5f,  0.5f, -0.5f, 0.6f,
    -0.5f, -0.5f, -0.5f, 0.6f,
    -0.5f, -0.5f, -0.5f, 0.6f,
    -0.5f, -0.5f,  0.5f, 0.6f,
    -0.5f,  0.5f,  0.5f, 0.6f,

    0.5f,  0.5f,  0.5f, 0.8f,
    0.5f,  0.5f, -0.5f, 0.8f,
    0.5f, -0.5f, -0.5f, 0.8f,
    0.5f, -0.5f, -0.5f, 0.8f,
    0.5f, -0.5f,  0.5f, 0.8f,
    0.5f,  0.5f,  0.5f, 0.8f,

    -0.5f, -0.5f, -0.5f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f,
    0.5f, -0.5f,  0.5f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,
     -0.5f, -0.5f,  0.5f, 1.0f,
     -0.5f, -0.5f, -0.5f, 1.0f,

     -0.5f,  0.5f, -0.5f, 0.3f,
     0.5f,  0.5f, -0.5f, 0.3f,
     0.5f,  0.5f,  0.5f, 0.3f,
     0.5f,  0.5f,  0.5f, 0.3f,
     -0.5f,  0.5f,  0.5f, 0.3f,
     -0.5f,  0.5f, -0.5f, 0.3f,
  };
  glm::mat4 cubes[4] = {
    glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.0f, 0.0f)),
    glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 0.0f)),
    glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 0.0f)),
    glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f))
  };
  // creating
  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // glGenBuffers(1, &EBO);
  // binding
  glBindVertexArray(VAO);
  // setting data for VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // setting data for EBO
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  // setting data for shader
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // unbinding
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  float lastTime;
  float time = glfwGetTime();
  while(!glfwWindowShouldClose(glWindow)) {
    lastTime = time;
    float time = glfwGetTime();
    float dt = lastTime - time;

    processInput(dt);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glBindVertexArray(VAO);
    shader.use();
    unsigned int shaderID = shader.getID();
    glm::mat4 model = glm::mat4(1.0f);
    float angle = glm::radians(glfwGetTime() * 180.0f);
    model = glm::rotate(model, angle, glm::vec3(1.0f, 1.0f, 1.0f));
    unsigned int viewLoc = glGetUniformLocation(shaderID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, camera.getViewMatrixPtr());
    unsigned int projLoc = glGetUniformLocation(shaderID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, camera.getProjectionMatrixPtr());
    unsigned int modelLoc = glGetUniformLocation(shaderID, "model");

    // camera
    float k = time;
    float r = 10.0f;
    glm::vec3 cameraPos = glm::vec3(sin(k)*r, 0.0f, cos(k) * r);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    camera.lookAt(cameraPos, target, up);


    for(int i = 0; i < 4; i++ ) {
      if(isMoving)
        cubes[i] = glm::rotate(cubes[i], glm::radians((float)i*5.0f / 3.0f), glm::vec3(1.0f, 1.0f, 0.0f));
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cubes[i]));
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);

    glfwSwapBuffers(glWindow);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
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
