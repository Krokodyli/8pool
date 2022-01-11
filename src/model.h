#pragma once

#include "../build/_deps/glad-build/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>

class Model {
private:
  unsigned int vaoID, vboID, eboID;
  unsigned int triangleCount;

  void createVAO(const std::vector<float> &vertices);
public:
  Model(const std::vector<float> &vertices);
  ~Model();

  void bind();
  unsigned int getTriangleCount();
};
