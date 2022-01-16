#pragma once

#include "drawable.h"
#include "physicalObject.h"
#include "resourceManager/resourceManager.h"

class PoolTable : public Drawable, public PhysicalObject {
private:
public:
  static constexpr float poolTableWidth = 1.12f;
  static constexpr float poolTableLength = 2.24f;

  PoolTable(ResourceManager &resourceManager, glm::vec3 initialPos);

  void load(ResourceManager &resourceManager);

  virtual glm::mat4 getTransformation();
};
