#pragma once

#include "../build/_deps/glad-build/include/glad/glad.h"
#include <GLFW/glfw3.h>
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
