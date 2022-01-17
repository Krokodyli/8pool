#pragma once

#include <vector>

class Mesh {
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
  Mesh(std::vector<float> &vertexData);
  Mesh(std::vector<float> &vertexData, std::vector<unsigned int> &indexData);
  Mesh(const Mesh &r) = delete;
  ~Mesh();

  unsigned int getID();
  void bind();
  void unbind();

  unsigned int getTriangleCount();
  bool hasIndexedVertices();
};
