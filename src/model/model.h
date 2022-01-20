#pragma once

#include "modelMaterial.h"

class Model {
private:
  bool loaded;
  bool lightSourceFlag;
  unsigned int meshID;
  ModelMaterial material;

  unsigned int textureID;
  glm::vec3 color;
  bool hasTexture;

public:
  Model();
  Model(unsigned int meshID, glm::vec3 color, ModelMaterial material);
  Model(unsigned int meshID, unsigned int textureID, ModelMaterial material);

  bool isLoaded();
  unsigned int getMeshID();
  ModelMaterial getMaterial();

  bool isTextured();
  unsigned int getTextureID();

  glm::vec3 getColor();
  void setColor(glm::vec3 value);

  bool isLightSource();
  void setLightSourceFlag(bool value);
};
