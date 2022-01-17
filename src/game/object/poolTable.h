#pragma once

#include "gameObject.h"
#include "physicalObject.h"
#include "../../model/model.h"

class PoolTable : public GameObject, public PhysicalObject {
private:
public:
  static constexpr float poolTableWidth = 1.12f;
  static constexpr float poolTableLength = 2.24f;

  PoolTable(Model model, glm::vec3 initialPos);

  virtual glm::mat4 getTransformation();
};
