#pragma once

#include "../model.h"

class Mesh {
public:
  virtual Model generateModel() = 0;
};
