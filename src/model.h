#pragma once

#include "glad.h"
#include "glfw.h"
#include <vector>

class Model {
private:
  unsigned int vao;
  unsigned int vbo;

  bool areVerticesIndexed;
  unsigned int ebo;

  unsigned int triangleCount;

  void createVAO(std::vector<float> &vertexData);
  void createIndexedVAO(std::vector<float> &vertexData,
                        std::vector<unsigned int> &indexData);

  void generateAndBindVertexArray();
  void generateAndBindVertexBuffer();
  void loadVertexData(std::vector<float> &vertexData);
  void setUpVertexAttributes();

  void generateAndBindElementArray();
  void loadIndexData(std::vector<unsigned int> &indexData);

public:
  Model(std::vector<float> &vertexData);
  Model(std::vector<float> &vertexData, std::vector<unsigned int> &indexData);
  ~Model();

  unsigned int getID();
  void bind();
  void unbind();

  unsigned int getTriangleCount();
  bool hasIndexedVertices();
};
