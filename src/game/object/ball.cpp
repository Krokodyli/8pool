#include "ball.h"

Ball::Ball(Model model, glm::vec3 initialPos) {
  this->model = model;
  initPhysicalObject(initialPos, ballMass);
}

void Ball::update(float dt, InputManager &inputManager) {
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
