#pragma once

#include <memory>
#include "../input/inputManager.h"

class Scene {
public:
  virtual void init() = 0;
  virtual void update(float dt) = 0;
  virtual void render() = 0;
  virtual bool shouldClose() = 0;
};
