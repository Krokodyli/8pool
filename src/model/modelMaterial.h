#pragma once

#include "../includes/glm.h"

struct ModelMaterial {
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float shininess;

  ModelMaterial();
  ModelMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
                float shininess);
};

struct ModelMaterials {
  static const ModelMaterial plastic;
  static const ModelMaterial fabric;
};
