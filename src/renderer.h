#pragma once

#include "camera.h"
#include "model.h"
#include "shader.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/trigonometric.hpp"

class Renderer {
private:
  Camera *camera;
  Shader *shader;

  Model *boundModel;

  void bindModelIfNecessary(Model *model);
public:
  Renderer();

  void render(Model *model, const glm::mat4 &transformation);

  Shader *getShader();
  void setShader(Shader *newShader);

  Camera *getCamera();
  void setCamera(Camera *camera);
};
