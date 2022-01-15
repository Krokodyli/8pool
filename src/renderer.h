#pragma once

#include "camera.h"
#include "drawable.h"
#include "model.h"
#include "resourceManager/resourceManager.h"
#include "shader.h"

class Renderer {
private:
  Camera *camera;
  Shader *shader;

  unsigned int boundModel;

  void bindModelIfNecessary(Model &model);
public:
  Renderer();

  void render(Drawable &drawable, ResourceManager &resourceManager);

  Shader *getShader();
  void setShader(Shader *newShader);

  Camera *getCamera();
  void setCamera(Camera *camera);
};
