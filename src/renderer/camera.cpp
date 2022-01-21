#include "camera.h"

Camera::Camera(float fov, float aspectRatio)
  : fov(fov), aspectRatio(aspectRatio) {
  nearDist = 0.1f;
  farDist = 100.0f;
  projection = glm::perspective(fov, aspectRatio, nearDist, farDist);
  view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  position = glm::vec3(0.0f, 0.0f, 3.0f);
}

Camera::Camera(float fov, float aspectRatio, float nearDist, float farDist)
  : Camera(fov, aspectRatio) {
  this->nearDist = nearDist;
  this->farDist = farDist;
}

void Camera::lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up) {
  view = glm::lookAt(eye, target, up);
  position = eye;
}

const glm::mat4 &Camera::getViewMat() {
  return view;
}

const glm::mat4 &Camera::getProjectionMat() {
  return projection;
}

float Camera::getAspectRatio() {
  return aspectRatio;
}
void Camera::setAspectRatio(float newAspectRatio) {
  aspectRatio = newAspectRatio;
}

const glm::vec3 &Camera::getPosition() {
  return position;
}
