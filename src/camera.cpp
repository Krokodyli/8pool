#include "camera.h"

Camera::Camera(float fov, float aspectRatio)
  : fov(fov), aspectRatio(aspectRatio) {
  projection = glm::perspective(fov, aspectRatio, nearDist, farDist);
  view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
}

void Camera::lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up) {
  view = glm::lookAt(eye, target, up);
}

const float *Camera::getViewMatrixPtr() {
  return glm::value_ptr(view);
}

const float *Camera::getProjectionMatrixPtr() {
  return glm::value_ptr(projection);
}

float Camera::getAspectRatio() {
  return aspectRatio;
}
void Camera::setAspectRatio(float newAspectRatio) {
  aspectRatio = newAspectRatio;
}
