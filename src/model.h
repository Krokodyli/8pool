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

  unsigned int triangleCount;

  void generateAndBindVertexArray();
  void generateAndBindVertexBuffer(const std::vector<float> &vertices);
  void generateAndBindNormalsBuffer(const std::vector<float> &normals);
  void generateAndBindIndicesBuffer(const std::vector<unsigned int> &indices);

  void createVAO(const std::vector<float> &vertices,
                 const std::vector<float> &normals);

  void createIndexedVAO(const std::vector<float> &vertices,
                        const std::vector<float> &normals,
                        const std::vector<unsigned int> &indices);

public:
  Model(const std::vector<float> &vertices, const std::vector<float> &normals);
  Model(const std::vector<float> &vertices, const std::vector<float> &normals,
        const std::vector<unsigned int> &indices);
  ~Model();

  void bind();
  void unbind();

  unsigned int getTriangleCount();
  bool hasIndexedVertices();
};
