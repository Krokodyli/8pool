#include "renderer.h"

Renderer::Renderer() {
  boundMesh = -1;
  camera = nullptr;
  shader = nullptr;
}

void Renderer::registerLights(std::vector<Light*> &lights) {
  shader->bindLights(lights);
}

void Renderer::render(GameObject &object, ResourceManager &resourceManager) {
  auto &model = object.getModel();

  auto &mesh = resourceManager.getMesh(model.getMeshID());
  bindMeshIfNecessary(mesh);

  unsigned int objectType;
  // --- object type ---
  // object without texture - 0
  // object with texture - 1
  // light source without texture - 2
  // light source with texture - 3

  if(model.isTextured()) {
    auto &texture = resourceManager.getTexture(model.getTextureID());
    texture.bind();
    objectType = 1;
  }
  else {
    shader->bindUniformVec3f("uColor", model.getColor());
    objectType = 0;
  }
  auto light = object.getObjectLight();
  if(light != nullptr) {
    objectType += 2;
  }

  auto material = model.getMaterial();
  shader->bindMaterial(material);

  shader->bindUniformUint("uObjectType", objectType);
  shader->bindUniformMat4f("uModel", object.getTransformation());

  shader->bindUniformMat4f("uView", camera->getViewMat());
  shader->bindUniformMat4f("uProjection", camera->getProjectionMat());

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
