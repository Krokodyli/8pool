#pragma once

#include "../../includes/glm.h"

class PhysicalObject {
protected:
  glm::quat rotation;
  glm::vec3 acceleration;
  glm::vec3 angularVelocity;
  glm::vec3 velocity;
  glm::vec3 position;
  float mass;
public:
  virtual void initPhysicalObject(glm::vec3 initialPos,
                                  float initialMass);
  virtual void updatePhysicalObject(float dt);

  virtual glm::vec3 getPosition();
  virtual void setPosition(glm::vec3 newPosition);

  virtual glm::vec3 getVelocity();
  virtual void setVelocity(glm::vec3 newVelocity);

  virtual glm::vec3 getAcceleration();
  virtual void setAcceleration(glm::vec3 newAcceleration);

  virtual glm::quat getRotation();
  virtual void setRotation(glm::quat newRotation);
};
