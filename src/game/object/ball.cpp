#include "ball.h"

Ball::Ball(Model model, glm::vec3 initialPos)
  : GameObject(model, initialPos) { }

void Ball::update(float dt, InputManager &inputManager) {
  auto tableBounds = glm::vec2(1.12f, 2.24f);
  if (position.x + ballRadius > tableBounds.x / 2.0f) {
    position.x = tableBounds.x / 2.0f - ballRadius;
    velocity.x *= -1;
  }
  if (position.x - ballRadius < -tableBounds.x / 2.0f) {
    position.x = -tableBounds.x / 2.0f + ballRadius;
    velocity.x *= -1;
  }
  if (position.z + ballRadius > tableBounds.y / 2.0f) {
    position.z = tableBounds.y / 2.0f - ballRadius;
    velocity.z *= -1;
  }
  if (position.z - ballRadius < -tableBounds.y / 2.0f) {
    position.z = -tableBounds.y / 2.0f + ballRadius;
    velocity.z *= -1;
  }
  angularVelocity = velocity / ballRadius;
  updatePhysicalObject(dt);
}
