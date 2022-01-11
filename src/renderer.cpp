#include "renderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include <cstdint>

Renderer::Renderer() {
  boundModel = nullptr;
  camera = nullptr;
  shader = nullptr;
}

void Renderer::render(Model *model, const glm::mat4 &transformation) {
  bindModelIfNecessary(model);
  shader->bindUniformMat4f("model", transformation);
  shader->bindUniformMat4f("view", camera->getViewMat());
  shader->bindUniformMat4f("projection", camera->getProjectionMat());
  shader->bindUniformVec3f("color", glm::vec3(0.0f, 0.5f, 0.5f));
  shader->bindUniformVec3f("viewPos", camera->getPosition());
  glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.0f));
  glm::vec3 lightPos = glm::vec3(translate * glm::vec4(camera->getPosition(), 3.0f));
  shader->bindUniformVec3f("lightPos", glm::vec3(3.0f, 0.0f, 0.0f));
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
