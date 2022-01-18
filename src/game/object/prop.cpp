#include "prop.h"

Prop::Prop(Model model, glm::vec3 initialPos)
  : GameObject(model, initialPos) { }

Prop::Prop(std::vector<Model> modelParts, glm::vec3 initialPos, std::vector<glm::vec3> partsRelativePositions) {
  initPhysicalObject(initialPos);
  this->modelParts = modelParts;
  modelPartsPositions = partsRelativePositions;
}

std::vector<glm::mat4> Prop::getTransformations() {
  if(modelParts.size() == 1)
    return GameObject::getTransformations();

  std::vector<glm::mat4> transformations;
  for(auto &relativePartPosition : modelPartsPositions) {
    glm::mat4 transformation(1.0f);
    transformation = glm::translate(transformation, position);
    transformation = glm::translate(transformation, relativePartPosition);
    transformations.push_back(transformation);
  }
  return transformations;
}
