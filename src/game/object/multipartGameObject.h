#pragma once

#include "gameObject.h"
#include "physicalObject.h"

class MultipartGameObject : public GameObject {
protected:
  std::vector<glm::vec3> modelPartsPositions;

public:
  MultipartGameObject() = default;
  MultipartGameObject(Model model, glm::vec3 initialPos);
  MultipartGameObject(std::vector<Model> models, glm::vec3 positions);
  MultipartGameObject(std::vector<Model> modelParts, glm::vec3 initialPos,
                      std::vector<glm::vec3> partsRelativePositions);

  virtual std::vector<glm::mat4> getTransformations();
};
