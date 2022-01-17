#include "renderer.h"

Renderer::Renderer() {
  boundMesh = -1;
  camera = nullptr;
  shader = nullptr;
}

void Renderer::render(GameObject &object, ResourceManager &resourceManager) {
  auto &model = object.getModel();

  auto &mesh = resourceManager.getMesh(model.getMeshID());
  bindMeshIfNecessary(mesh);

  if(model.isTextured()) {
    auto &texture = resourceManager.getTexture(model.getTextureID());
    texture.bind();
  }
  else {
    shader->bindUniformVec3f("color", model.getColor());
  }

  auto material = model.getMaterial();
  shader->bindMaterial(material);

  shader->bindUniformMat4f("model", object.getTransformation());

  shader->bindUniformMat4f("view", camera->getViewMat());
  shader->bindUniformMat4f("projection", camera->getProjectionMat());

  shader->bindUniformVec3f("viewPos", camera->getPosition());

  if (mesh.hasIndexedVertices())
    glDrawElements(GL_TRIANGLES, mesh.getTriangleCount() * 3, GL_UNSIGNED_INT,
                   0);
  else
    glDrawArrays(GL_TRIANGLES, 0, mesh.getTriangleCount());
}

Shader *Renderer::getShader() { return shader; }

void Renderer::setCamera(Camera *newCamera) { camera = newCamera; }

void Renderer::setShader(Shader *newShader) {
  shader = newShader;
  shader->use();
}

Camera *Renderer::getCamera() { return camera; }

void Renderer::bindMeshIfNecessary(Mesh &mesh) {
  unsigned int meshID = mesh.getID();
  if (boundMesh != meshID) {
    boundMesh = meshID;
    mesh.bind();
  }
}
