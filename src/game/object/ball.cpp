#include "ball.h"

Ball::Ball(Model model, glm::vec3 initialPos, BallController *controller)
    : GameObject(model, initialPos), controller(controller) {}

void Ball::update(float dt) {
  if (controller != nullptr && !controller->getMoveFlag())
    return;

  auto tableBounds = glm::vec2(PoolTable::width, PoolTable::length);
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

void Ball::setController(BallController *newController) {
  controller = newController;
}
