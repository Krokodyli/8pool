#pragma once

#include "../model.h"
#include <memory>

class Mesh {
public:
  virtual std::unique_ptr<Model> generateModel() = 0;
};
