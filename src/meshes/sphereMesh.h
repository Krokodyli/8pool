#pragma once

#include "../glm.h"
#include "mesh.h"
#include <math.h>

class SphereMesh : public Mesh {
private:
  std::vector<float> verticesF;
  std::vector<float> normalsF;
  std::vector<unsigned int> indices;

  float radius;
  unsigned int precision;

  void generateMesh();
  void generateNormals();

  void generateInitialMesh(std::vector<glm::vec3> &vertices);
  void divideTriangle(std::vector<glm::vec3> &vertices,
                      unsigned int indicesOffset);

  void generateFloatVertices(std::vector<glm::vec3> &vertices);
  void generateFloatNormals(std::vector<glm::vec3> &vertices);

public:
  SphereMesh(float radius, unsigned int precision = 4);

  Model generateModel();
};
