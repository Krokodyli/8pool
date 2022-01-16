#include "ball.h"

Ball::Ball(ResourceManager &resourceManager, glm::vec3 initialPos) {
  initPhysicalObject(initialPos, ballMass);
  loadResources(resourceManager);
}

void Ball::loadResources(ResourceManager &resourceManager) {
  modelID = resourceManager.getModelID("ball");
  textureID = resourceManager.getTextureID("sphere.png");
}

void Ball::update(float dt) {
  angularVelocity = velocity / ballRadius;
  updatePhysicalObject(dt);
  auto tableBounds = glm::vec2(1.12f, 2.24f);
  auto pyk = false;
  if(position.x > tableBounds.x / 2.0f) {
    position.x = tableBounds.x / 2.0f;
    pyk = true;
  } if(position.x < -tableBounds.x / 2.0f) {
    position.x = -tableBounds.x / 2.0f;
    pyk = true;
  }
  if (position.z > tableBounds.y / 2.0f) {
    position.z = tableBounds.y / 2.0f;
    pyk = true;
  } if (position.z < -tableBounds.y / 2.0f) {
    position.z = -tableBounds.y / 2.0f;
    pyk = true;
  }
  if(pyk) velocity *= -1;
}

glm::mat4 Ball::getTransformation() {
  glm::mat4 rotationMat = glm::toMat4(rotation);
  auto translationMat = glm::translate(glm::mat4(1.0f), position);
  return translationMat * rotationMat;
}
