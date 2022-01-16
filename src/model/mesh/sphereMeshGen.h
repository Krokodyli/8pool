#pragma once

#include "../../includes/glm.h"
#include "meshGenerator.h"
#include <math.h>
#include <memory>

class SphereMeshGenerator : public MeshGenerator {
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
  SphereMeshGenerator(float radius, unsigned int precision = 4);

  std::unique_ptr<Mesh> getMesh();
};
