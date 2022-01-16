#pragma once

#include "camera.h"
#include "drawable.h"
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

  void render(Drawable &drawable, ResourceManager &resourceManager);

  Shader *getShader();
  void setShader(Shader *newShader);

  Camera *getCamera();
  void setCamera(Camera *camera);
};
