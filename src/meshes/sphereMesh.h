#pragma once

#include "../glm.h"
#include "mesh.h"
#include <math.h>

class SphereMesh : public Mesh {
private:
  std::vector<float> vertexData;
  std::vector<unsigned int> indexData;

  float radius;
  unsigned int precision;

  void generateMesh();
  void generateNormals();

  void generateInitialMesh(std::vector<glm::vec3> &vertices);
  void divideTriangle(std::vector<glm::vec3> &vertices,
                      unsigned int indicesOffset);

  void generateVertexData(std::vector<glm::vec3> &vertices);
  void addVertexToVertexData(glm::vec3 vertex, bool offsetTexture);

public:
  SphereMesh(float radius, unsigned int precision = 4);

  Model generateModel();
};
