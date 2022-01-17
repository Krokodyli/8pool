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

  unsigned int boundMesh;

  void bindMeshIfNecessary(Mesh &mesh);
public:
  Renderer();

  void registerLights(std::vector<Light*> &lights);
  void render(GameObject &object, ResourceManager &resourceManager);

  Shader *getShader();
  void setShader(Shader *newShader);

  Camera *getCamera();
  void setCamera(Camera *camera);
};
