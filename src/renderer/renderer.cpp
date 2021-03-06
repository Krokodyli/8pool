#include "renderer.h"

Renderer::Renderer() {
  boundMesh = -1;
  boundTexture = -1;
  camera = nullptr;
  shader = nullptr;
  fogFactor = 0.0f;
}

void Renderer::prepareView() {
  shader->bindUniformMat4f(SHAD_LOC_VIEW_MAT, camera->getViewMat());
  shader->bindUniformMat4f(SHAD_LOC_PROJECTION_MAT, camera->getProjectionMat());
  shader->bindUniformVec3f(SHAD_LOC_VIEW_POS, camera->getPosition());

  shader->bindUniformFloat(SHAD_LOC_FOG_FACTOR, fogFactor);
  shader->bindUniformVec3f(SHAD_LOC_FOG_COLOR, glm::vec3(0.57f, 0.59f, 0.59f));
}

void Renderer::registerLights(std::vector<Light *> &lights) {
  shader->bindLights(lights);
}

void Renderer::render(GameObject &object, ResourceManager &resourceManager) {
  auto modelParts = object.getModelParts();
  auto transformations = object.getTransformations();
  for(int i = 0; i < modelParts.size(); i++) {
    auto &model = modelParts[i];

    unsigned int objectType = 0;
    // --- object type ---
    // object without texture - 0
    // object with texture - 1
    // light source without texture - 2
    // light source with texture - 3

    // mesh
    int meshID = model.getMeshID();
    auto &mesh = resourceManager.getMesh(meshID);
    if(boundMesh != meshID) {
      boundMesh = meshID;
      mesh.bind();
    }
    // texture or color
    if (model.isTextured()) {
      int textureID = model.getTextureID();
      if(textureID != boundTexture) {
        boundTexture = textureID;
        resourceManager.getTexture(model.getTextureID()).bind();
      }
      objectType += 1;
    } else {
      shader->bindUniformVec3f(SHAD_LOC_COLOR, model.getColor());
    }
    if(model.isLightSource())
      objectType += 2;

    auto material = model.getMaterial();
    shader->bindMaterial(material);

    shader->bindUniformUint(SHAD_LOC_OBJ_TYPE, objectType);
    auto transformation = transformations[i];
    auto normalTransformation =
      glm::transpose(glm::inverse(glm::mat3(transformation)));
    shader->bindUniformMat4f(SHAD_LOC_MODEL_MAT, transformation);

    shader->bindUniformMat3f(SHAD_LOC_NORMAL_MAT, normalTransformation);

    if (mesh.hasIndexedVertices())
      glDrawElements(GL_TRIANGLES, mesh.getTriangleCount() * 3, GL_UNSIGNED_INT,
                    0);
    else
      glDrawArrays(GL_TRIANGLES, 0, mesh.getTriangleCount());
  }
}

Shader *Renderer::getShader() { return shader; }

void Renderer::setCamera(Camera *newCamera) { camera = newCamera; }

void Renderer::setShader(Shader *newShader) {
  shader = newShader;
  shader->use();
}

Camera *Renderer::getCamera() { return camera; }

void Renderer::setFogFactor(float newFogFactor) {
  fogFactor = newFogFactor;
  fogFactor = std::min(1.0f, fogFactor);
  fogFactor = std::max(0.0f, fogFactor);
}

float Renderer::getFogFactor() {
  return fogFactor;
}

void Renderer::bindMeshIfNecessary(Mesh &mesh) {
  unsigned int meshID = mesh.getID();
  if (boundMesh != meshID) {
    boundMesh = meshID;
    mesh.bind();
  }
}
