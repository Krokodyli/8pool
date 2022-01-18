#pragma once

#include "../../includes/glm.h"
#include "meshGenerator.h"
#include <memory>
#include <vector>

class CuboidMeshGenerator : public MeshGenerator {
private:
  std::vector<float> vertexData;

  void generateMesh(float xSize, float ySize, float zSize);
  void addTriangleToVertexData(glm::vec3 vertices[4],
                               glm::vec3 normal,
                               glm::vec2 texCoords[4],
                               unsigned int indices[3]);

public:
  CuboidMeshGenerator(float xSize = 1.0f, float ySize = 1.0f,
                      float zSize = 1.0f);
  std::unique_ptr<Mesh> getMesh();
};
