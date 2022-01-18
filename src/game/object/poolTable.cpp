#include "poolTable.h"

PoolTable::PoolTable(Model fabricModel, Model tableSideX, Model tableSideY, Model tableSideZ, Model tableLeg,  glm::vec3 initialPos) {
  initPhysicalObject(initialPos);
  initModels(fabricModel, tableSideX, tableSideY, tableSideZ, tableLeg);
}

glm::mat4 PoolTable::getTransformation() {
  glm::mat4 transformation(1.0f);
  transformation = glm::translate(transformation, position);
  return transformation;
}

void PoolTable::initModels(Model fabricModel, Model tableSideX, Model tableSideY, Model tableSizeZ, Model tableLeg) {
  modelParts.push_back(fabricModel);
  modelPartsPositions.push_back(glm::vec3(0.0f, -topThickness * 0.5f, 0.0f));

  float zPos = (length + borderThickness) * 0.5f;
  modelParts.push_back(tableSideX);
  modelPartsPositions.push_back(glm::vec3(0.0f, 0.0f, zPos));

  modelParts.push_back(tableSideX);
  modelPartsPositions.push_back(glm::vec3(0.0f, 0.0f, -zPos));

  // modelParts.push_back(tableSideY);
  // modelPartsPositions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

  float xPos = (width + borderThickness) * 0.5f;
  modelParts.push_back(tableSizeZ);
  modelPartsPositions.push_back(glm::vec3(xPos, 0.0f, 0.0f));

  modelParts.push_back(tableSizeZ);
  modelPartsPositions.push_back(glm::vec3(-xPos, 0.0f, 0.0f));

  for(int i = 0; i < 4; i++) {
    float xPos = (width + borderThickness) * 0.5f;
    if(i%2 == 1) xPos *= -1;
    float yPos = -legLength/2.0f;
    float zPos = (length + borderThickness) * 0.5f;
    if(i/2 == 1) zPos *= -1;
    modelParts.push_back(tableLeg);
    modelPartsPositions.push_back(glm::vec3(xPos, yPos, zPos));
  }
}
