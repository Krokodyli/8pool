#include "poolTable.h"

PoolTable::PoolTable(Model model, glm::vec3 initialPos) {
  this->model = model;
  initPhysicalObject(initialPos, 100.0f);
}

glm::mat4 PoolTable::getTransformation() {
  glm::mat4 transformation(1.0f);
  transformation = glm::translate(transformation, position);
  return transformation;
}
