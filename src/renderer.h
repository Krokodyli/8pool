#pragma once

#include "camera.h"
#include "model.h"
#include "shader.h"

class Renderer {
private:
  Camera *camera;
  Shader *shader;

  unsigned int boundModel;

  void bindModelIfNecessary(Model &model);
public:
  Renderer();

  void render(Model &model, const glm::mat4 &transformation);
  void renderLight(Model &model);

  Shader *getShader();
  void setShader(Shader *newShader);

  Camera *getCamera();
  void setCamera(Camera *camera);
};
