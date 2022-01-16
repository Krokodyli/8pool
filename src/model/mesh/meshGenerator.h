#pragma once

#include "mesh.h"
#include <memory>

class MeshGenerator {
public:
  virtual std::unique_ptr<Mesh> getMesh() = 0;
};
