#pragma once

#include "../../includes/glm.h"
#include "../../light/light.h"
#include "../../inputManager.h"
#include "../../model/model.h"
#include "physicalObject.h"
#include <stdexcept>
#include <vector>

class GameObject : public PhysicalObject {
protected:
  std::vector<Model> modelParts;
public:
  GameObject();
  GameObject(Model model, glm::vec3 initialPos);

  virtual void update(float dt, InputManager &inputManager);

  virtual std::vector<glm::mat4> getTransformations();
  virtual std::vector<Model> &getModelParts();
  virtual std::vector<Light*> getModelLights();
};
