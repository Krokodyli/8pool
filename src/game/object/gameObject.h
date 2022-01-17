#pragma once

#include "../../includes/glm.h"
#include "../../inputManager.h"
#include "../../model/model.h"

class GameObject {
protected:
  Model model;

  bool cleanUpFlag;

public:
  virtual void update(float dt, InputManager &inputManager);

  virtual glm::mat4 getTransformation();
  virtual Model &getModel();

  virtual bool shouldCleanUp();
};
