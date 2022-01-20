#pragma once

#include "camera.h"
#include "game/object/gameObject.h"
#include "model/mesh/mesh.h"
#include "resourceManager/resourceManager.h"
#include "shader.h"

class Renderer {
private:
  Camera *camera;
  Shader *shader;

  int boundMesh;
  int boundTexture;

  float fogFactor;

  void bindMeshIfNecessary(Mesh &mesh);
public:
  Renderer();

  void prepareView();
  void registerLights(std::vector<Light*> &lights);
  void render(GameObject &object, ResourceManager &resourceManager);

  Shader *getShader();
  void setShader(Shader *newShader);

  Camera *getCamera();
  void setCamera(Camera *camera);

  void setFogFactor(float newFogFactor);
  float getFogFactor();
};
