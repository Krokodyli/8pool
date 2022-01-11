#include "renderer.h"
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
  shader->bindUniformVec4f("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
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
