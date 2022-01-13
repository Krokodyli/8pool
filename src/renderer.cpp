#include "renderer.h"
#include <cstdint>
#include <iostream>

Renderer::Renderer() {
  boundModel = nullptr;
  camera = nullptr;
  shader = nullptr;
}

void Renderer::render(Model *model, const glm::mat4 &transformation) {
  float time = glfwGetTime();
  glm::mat4 lightTrans =
    glm::translate(glm::mat4(1.0f), glm::vec3(3*cos(time), 0.0f, 3*sin(time)));

  bindModelIfNecessary(model);
  shader->bindUniformMat4f("model", transformation);
  shader->bindUniformMat4f("view", camera->getViewMat());
  shader->bindUniformMat4f("projection", camera->getProjectionMat());
  shader->bindUniformVec3f("color", glm::vec3(1.0f, 1.0f, 1.0f));
  shader->bindUniformVec3f("viewPos", camera->getPosition());

  glm::vec3 lightPos = glm::vec3(lightTrans * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  shader->bindUniformVec3f("lightPos", lightPos);

  glDrawArrays(GL_TRIANGLES, 0, model->getTriangleCount());
}

void Renderer::renderLight(Model *model) {
  float time = glfwGetTime();
  glm::mat4 lightTrans = glm::translate(
      glm::mat4(1.0f), glm::vec3(3 * cos(time), 0.0f, 3 * sin(time)));
  lightTrans = glm::scale(lightTrans, glm::vec3(0.5f, 0.5f, 0.5f));

  bindModelIfNecessary(model);
  shader->bindUniformMat4f("model", lightTrans);
  shader->bindUniformMat4f("view", camera->getViewMat());
  shader->bindUniformMat4f("projection", camera->getProjectionMat());
  shader->bindUniformVec3f("color", glm::vec3(1.0f, 1.0f, 0.3f));
  shader->bindUniformVec3f("viewPos", camera->getPosition());
  shader->bindUniformVec3f("lightPos", glm::vec3(-1.0f, 0.0f, 0.0f));

  glDrawArrays(GL_TRIANGLES, 0, model->getTriangleCount());
}

Shader *Renderer::getShader() { return shader; }

void Renderer::setCamera(Camera *newCamera) {
  camera = newCamera;
}

void Renderer::setShader(Shader *newShader) {
  shader = newShader;
  shader->use();
}

Camera *Renderer::getCamera() {
  return camera;
}

void Renderer::bindModelIfNecessary(Model *model) {
  if (boundModel != model) {
    boundModel = model;
    boundModel->bind();
  }
}
