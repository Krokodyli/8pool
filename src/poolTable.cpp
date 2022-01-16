#include "poolTable.h"

PoolTable::PoolTable(ResourceManager &resourceManager, glm::vec3 initialPos) {
  initPhysicalObject(initialPos, 100.0f);
  initDrawable();
  load(resourceManager);
}

void PoolTable::load(ResourceManager &resourceManager) {
  meshID = resourceManager.getMeshID("poolTable");
  textureID = resourceManager.getTextureID("poolTable.png");
}

glm::mat4 PoolTable::getTransformation() {
  glm::mat4 transformation(1.0f);
  transformation = glm::translate(transformation, position);
  return transformation;
}
