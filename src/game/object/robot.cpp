#include "robot.h"

Robot::Robot(Model headModel, Model noseModel, glm::vec3 initialPos,
             RobotController *controller)
    : controller(controller) {
  initPhysicalObject(initialPos);
  initModels(headModel, noseModel);
  if (controller != nullptr)
    controller->init(*this);
  initLight();
  isLightTurnedOn = true;
  toggleLight();
}

void Robot::update(float dt) {
  updatePhysicalObject(dt);
  if (controller != nullptr)
    controller->control(*this);
}

std::vector<Light *> Robot::getModelLights() {
  if (!isLightTurnedOn)
    return {};

  light.position = position + glm::rotate(rotation, modelPartsPositions[1]);
  light.direction =
      glm::normalize(glm::rotate(rotation, modelPartsPositions[1]));
  return {&light};
}

void Robot::setController(RobotController *newController) {
  controller = newController;
  controller->init(*this);
}

void Robot::toggleLight() {
  isLightTurnedOn = !isLightTurnedOn;
  glm::vec3 noseColor =
      isLightTurnedOn ? glm::vec3(1.0f, 1.0f, 1.0f) : glm::vec3(0.0f);

  auto meshID = modelParts[1].getMeshID();
  auto material = modelParts[1].getMaterial();
  modelParts[1] = Model(meshID, noseColor, material);
  modelParts[1].setLightSourceFlag(isLightTurnedOn);
}

void Robot::initModels(Model headModel, Model noseModel) {
  modelParts.push_back(headModel);
  modelPartsPositions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
  modelParts.push_back(noseModel);
  modelPartsPositions.push_back(
      glm::vec3(0.0f, 0.0f, -(headSize + noseLength) / 2.0f));
}

void Robot::initLight() {
  light.lightType = LightType::spotlight;

  light.attenuation = glm::vec3(1.0f, 0.09f, 0.032f);

  light.ambient = glm::vec3(0.0f);
  light.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
  light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

  light.cutOff.x = cos(glm::radians(25.0f));
  light.cutOff.y = cos(glm::radians(35.0f));
}
