#include "multipartGameObject.h"

MultipartGameObject::MultipartGameObject(Model model, glm::vec3 initialPos)
  : GameObject(model, initialPos) { }

MultipartGameObject::MultipartGameObject(
    std::vector<Model> modelParts, glm::vec3 initialPos,
    std::vector<glm::vec3> partsRelativePositions) {
  initPhysicalObject(initialPos);
  this->modelParts = modelParts;
  modelPartsPositions = partsRelativePositions;
}

std::vector<glm::mat4> MultipartGameObject::getTransformations() {
  if(modelParts.size() == 1)
    return GameObject::getTransformations();

  std::vector<glm::mat4> transformations;
  glm::mat4 rotationMat = glm::toMat4(rotation);
  for(auto &relativePartPosition : modelPartsPositions) {
    glm::mat4 transformation(1.0f);
    transformation = glm::translate(transformation, position);
    transformation = transformation * rotationMat;
    transformation = glm::translate(transformation, relativePartPosition);
    transformations.push_back(transformation);
  }
  return transformations;
}
