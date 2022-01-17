#pragma once

#include "../../includes/glm.h"
#include "../../light/light.h"
#include "../../inputManager.h"
#include "../../model/model.h"
#include "physicalObject.h"
#include <stdexcept>

class GameObject : public PhysicalObject {
protected:
  Model model;

  bool cleanUpFlag;

public:
  virtual void update(float dt, InputManager &inputManager);

  virtual bool isVisible();
  virtual glm::mat4 getTransformation();
  virtual Model &getModel();

  virtual Light *getObjectLight();

  virtual bool shouldCleanUp();
};
