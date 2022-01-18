#include "physicalObject.h"

void PhysicalObject::initPhysicalObject(glm::vec3 initialPosition) {
  position = initialPosition;
  velocity = glm::vec3(0.0f);
  acceleration = glm::vec3(0.0f);
  rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
  angularVelocity = glm::vec3(0.0f);
}

void PhysicalObject::updatePhysicalObject(float dt) {
  velocity += acceleration * dt;
  position += velocity * dt;

  if (angularVelocity != glm::vec3(0.0f)) {
    auto axis = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), angularVelocity);
    axis = glm::normalize(axis);
    auto angle = dt * glm::length(angularVelocity);
    rotation = rotation * glm::angleAxis(angle, axis);
  }
}

glm::vec3 PhysicalObject::getPosition() { return position; }
void PhysicalObject::setPosition(glm::vec3 newPosition) {
  position = newPosition;
}

glm::vec3 PhysicalObject::getVelocity() { return velocity; }

void PhysicalObject::setVelocity(glm::vec3 newVelocity) {
  velocity = newVelocity;
}

glm::vec3 PhysicalObject::getAcceleration() { return acceleration; }

void PhysicalObject::setAcceleration(glm::vec3 newAcceleration) {
  acceleration = newAcceleration;
}

glm::quat PhysicalObject::getRotation() { return rotation; }

void PhysicalObject::setRotation(glm::quat newRotation) {
  rotation = newRotation;
}
