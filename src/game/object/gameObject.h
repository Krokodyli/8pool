#pragma once

#include "../../includes/glm.h"
#include "../../inputManager.h"
#include "../../model/model.h"
#include "physicalObject.h"

class GameObject : public PhysicalObject {
protected:
  Model model;

  bool cleanUpFlag;

public:
  virtual void update(float dt, InputManager &inputManager);

  virtual glm::mat4 getTransformation();
  virtual Model &getModel();

  virtual bool shouldCleanUp();
};
