#pragma once

#include "glm.h"
#include "resourceManager/resourceManager.h"
#include "physicalObject.h"
#include "drawable.h"

class Ball : public Drawable, public PhysicalObject {
public:
  static constexpr float ballRadius = 0.0285;
  static constexpr float ballMass = 0.165;

  Ball(ResourceManager &resourceManager, glm::vec3 initialPos);

  void loadResources(ResourceManager &resourceManager);
  void update(float dt);

  glm::mat4 getTransformation();
};
