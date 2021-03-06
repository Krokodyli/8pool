#pragma once

#include "../includes/glm.h"

class Camera {
private:
  float nearDist;
  float farDist;

  float fov;
  float aspectRatio;
  glm::mat4 view;
  glm::mat4 projection;
  glm::vec3 position;

public:
  Camera(float fov, float aspectRatio);

  Camera(float fov, float aspectRatio, float nearDist, float farDist);

  void lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up);

  const glm::mat4 &getViewMat();

  const glm::mat4 &getProjectionMat();

  float getAspectRatio();
  void setAspectRatio(float newAspectRatio);

  const glm::vec3 &getPosition();
};
