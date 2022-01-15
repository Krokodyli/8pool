#include "physicalObject.h"

void PhysicalObject::initPhysicalObject(glm::vec3 initialPosition,
                                        float initialMass) {
  position = initialPosition;
  velocity = glm::vec3(0.0f);
  acceleration = glm::vec3(0.0f);
  rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
  mass = initialMass;
}

void PhysicalObject::updatePhysicalObject(float dt) {
  velocity += acceleration * dt;
  position += velocity * dt;
}

glm::vec3 PhysicalObject::getVelocity() {
  return velocity;
}

void PhysicalObject::setVelocity(glm::vec3 newVelocity) {
  velocity = newVelocity;
}

glm::vec3 PhysicalObject::getAcceleration() {
  return acceleration;
}

void PhysicalObject::setAcceleration(glm::vec3 newAcceleration) {
  acceleration = newAcceleration;
}

glm::quat PhysicalObject::getRotation() {
  return rotation;
}

void PhysicalObject::setRotation(glm::quat newRotation) {
  rotation = newRotation;
}
