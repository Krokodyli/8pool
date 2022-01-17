#pragma once

#include "includes/glm.h"

enum LightSourceType {
  point,
  directional,
  spotlight
};

struct LightSource {
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
