#pragma once

#include "../includes/glm.h"

enum class LightType {
  point = 1,
  spotlight = 2
};

struct Light {
  LightType lightType;

  glm::vec3 position;
  glm::vec3 direction;

  // coefficient for spotlight
  glm::vec2 cutOff;
  // x - cutOff coefficient
  // y - outerCutOff coefficient

  glm::vec3 attenuation;
  // attenuation.x - constant coefficient
  // attenuation.y - linear coefficient
  // attenuation.z - quadratic coefficient

  // coefficient for each lighting type
  // xyz -> rgb
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
};
