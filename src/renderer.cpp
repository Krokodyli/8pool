#include "renderer.h"

Renderer::Renderer() {
  boundModel = -1;
  camera = nullptr;
  shader = nullptr;
}

void Renderer::render(Drawable &drawable, ResourceManager &resourceManager) {
  Model &model = resourceManager.getModel(drawable.getModelID());
  resourceManager.getTexture(drawable.getTextureID()).bind();
  bindModelIfNecessary(model);

  shader->bindUniformMat4f("model", drawable.getTransformation());
  shader->bindUniformMat4f("view", camera->getViewMat());
  shader->bindUniformMat4f("projection", camera->getProjectionMat());

  shader->bindUniformVec3f("color", glm::vec3(1.0f, 1.0f, 1.0f));
  shader->bindUniformVec3f("viewPos", camera->getPosition());

  glm::mat4 lightTrans = glm::mat4(1.0f);
  lightTrans = glm::translate(lightTrans, glm::vec3(-3.0f, 0.0f, -2.0f));
  lightTrans = glm::scale(lightTrans, glm::vec3(0.5f, 0.5f, 0.5f));
  glm::vec3 lightPos =
      glm::vec3(lightTrans * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  shader->bindUniformVec3f("lightPos", lightPos);

  if (model.hasIndexedVertices())
    glDrawElements(GL_TRIANGLES, model.getTriangleCount() * 3, GL_UNSIGNED_INT,
                   0);
  else
    glDrawArrays(GL_TRIANGLES, 0, model.getTriangleCount());
}

Shader *Renderer::getShader() { return shader; }

void Renderer::setCamera(Camera *newCamera) { camera = newCamera; }

void Renderer::setShader(Shader *newShader) {
  shader = newShader;
  shader->use();
}

Camera *Renderer::getCamera() { return camera; }

void Renderer::bindModelIfNecessary(Model &model) {
  unsigned int modelID = model.getID();
  if (boundModel != modelID) {
    boundModel = modelID;
    model.bind();
  }
}
