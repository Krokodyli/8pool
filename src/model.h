#pragma once

#include "glad.h"
#include "glfw.h"
#include <vector>

class Model {
private:
  unsigned int modelVAO;
  unsigned int verticesVBO;
  unsigned int normalsVBO;
  unsigned int indicesEBO;
  bool areVerticesIndexed;

  unsigned int triangleCount;

  void generateAndBindVertexArray();
  void generateAndBindVertexBuffer(std::vector<float> &vertices);
  void generateAndBindNormalsBuffer(std::vector<float> &normals);
  void generateAndBindIndicesBuffer(std::vector<unsigned int> &indices);

  void createVAO(std::vector<float> &vertices, std::vector<float> &normals);

  void createIndexedVAO(std::vector<float> &vertices,
                        std::vector<float> &normals,
                        std::vector<unsigned int> &indices);

public:
  Model(std::vector<float> &vertices, std::vector<float> &normals);
  Model(std::vector<float> &vertices, std::vector<float> &normals,
        std::vector<unsigned int> &indices);
  ~Model();

  unsigned int getID();
  void bind();
  void unbind();

  unsigned int getTriangleCount();
  bool hasIndexedVertices();
};
