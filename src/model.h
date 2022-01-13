#pragma once

#include "glad.h"
#include "glfw.h"
#include <vector>

class Model {
private:
  unsigned int vaoID, vbo1ID, vbo2ID;
  unsigned int triangleCount;

  void createVAO(const std::vector<float> &vertices,
                 const std::vector<float> &normals);
public:
  Model(const std::vector<float> &vertices,
        const std::vector<float> &normals);
  ~Model();

  void bind();
  unsigned int getTriangleCount();
};
