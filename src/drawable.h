#pragma once

#include "includes/glm.h"

class Drawable {
protected:
  int meshID;
  bool hasTexture;
  int textureID;

public:
  virtual void initDrawable();
  virtual glm::mat4 getTransformation() = 0;
  virtual int getTextureID();
  virtual int getMeshID();
};
