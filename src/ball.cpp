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
  updatePhysicalObject(dt);
}

glm::mat4 Ball::getTransformation() {
  glm::mat4 transformation(1.0f);
  transformation = glm::translate(transformation, position);
  return transformation;
}
