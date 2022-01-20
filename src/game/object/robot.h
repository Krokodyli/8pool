#pragma once

#include "../../model/model.h"
#include "../controller/robotController.h"
#include "multipartGameObject.h"

class Robot : public MultipartGameObject {
private:
  static constexpr float robotSpeed = 0.0f;
  RobotController *controller;
  Light light;
  bool isLightTurnedOn;

  void initModels(Model headModel, Model noseModel);
  void initLight();

public:
  static constexpr float headSize = 0.5f;
  static constexpr float noseThickness = 0.05f;
  static constexpr float noseLength = 0.1f;

  Robot(Model headModel, Model noseModel, glm::vec3 initialPos,
        RobotController *robotController = nullptr);
  void update(float dt);

  std::vector<Light *> getModelLights();

  void setController(RobotController *newController);
  void toggleLight();

};
