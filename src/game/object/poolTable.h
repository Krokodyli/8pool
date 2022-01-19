#pragma once

#include "../../model/model.h"
#include "prop.h"
#include "physicalObject.h"

class PoolTable : public Prop {
private:
  void initModels(Model fabricModel, Model tableSideX, Model tableSideY,
                  Model tableSideZ, Model tableLeg);

public:
  static constexpr float borderThickness = 0.05f;
  static constexpr float width = 1.12f;
  static constexpr float length = 2.24f;
  static constexpr float topThickness = 0.05f;
  static constexpr float legLength = 0.75f;

  PoolTable(Model fabricModel, Model tableSideX, Model tableSideY,
            Model tableSideZ, Model tableLeg, glm::vec3 initialPos);
};
