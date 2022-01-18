#pragma once

#include "gameObject.h"
#include "physicalObject.h"

class Prop : public GameObject {
protected:
  std::vector<glm::vec3> modelPartsPositions;

public:
  Prop() = default;
  Prop(Model model, glm::vec3 initialPos);
  Prop(std::vector<Model> models, glm::vec3 positions);
  Prop(std::vector<Model> modelParts, glm::vec3 initialPos,
       std::vector<glm::vec3> partsRelativePositions);

  virtual std::vector<glm::mat4> getTransformations();
};
