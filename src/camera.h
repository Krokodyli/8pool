#pragma once

#include "glm/detail/func_trigonometric.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera {
private:
  const float nearDist = 0.1f, farDist = 100.0f;

  float fov;
  float aspectRatio;
  glm::mat4 view;
  glm::mat4 projection;

public:
  Camera(float fov, float aspectRatio);

  void lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up);

  const glm::mat4 &getViewMat();

  const glm::mat4 &getProjectionMat();

  float getAspectRatio();
  void setAspectRatio(float newAspectRatio);
};
