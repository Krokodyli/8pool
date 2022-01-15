#include "sphereMesh.h"

SphereMesh::SphereMesh(float radius, unsigned int precision)
    : radius(radius), precision(precision) {
  generateMesh();
}

std::unique_ptr<Model> SphereMesh::generateModel() {
  return std::make_unique<Model>(vertexData, indexData);
}

void SphereMesh::generateMesh() {
  std::vector<glm::vec3> vertices;
  generateInitialMesh(vertices);
  for (int i = 0; i < precision; i++) {
    unsigned int triangleOffset = 0;
    unsigned int oldIndexDataSize = indexData.size();
    for (; triangleOffset < oldIndexDataSize; triangleOffset += 3)
      divideTriangle(vertices, triangleOffset);
  }
  generateVertexData(vertices);
}

void SphereMesh::generateInitialMesh(std::vector<glm::vec3> &vertices) {
  float r = radius;
  float r2 = radius * sqrt(2.0f) / 2.0f;
  // generating upper pyramid vertices
  vertices.push_back({0.0f, r, 0.0f});
  vertices.push_back({r2, 0.0f, -r2});
  vertices.push_back({r2, 0.0f, r2});
  vertices.push_back({-r2, 0.0f, r2});
  vertices.push_back({-r2, 0.0f, -r2});
  // generating triangles
  for (int i = 0; i < 4; i++) {
    int j = (i + 1) % 4;
    indexData.push_back(i + 1);
    indexData.push_back(j + 1);
    indexData.push_back(0);
  }
}

void SphereMesh::divideTriangle(std::vector<glm::vec3> &vertices,
                                unsigned int indicesOffset) {
  /*
    triangle division

            a
          /  \
         /    \
        ac     bc
       / \    / \
      /   \  /   \
     c-----cb-----b
  */
  unsigned int aPos = indexData[indicesOffset];
  unsigned int bPos = indexData[indicesOffset + 1];
  unsigned int cPos = indexData[indicesOffset + 2];
  glm::vec3 a = vertices[aPos];
  glm::vec3 b = vertices[bPos];
  glm::vec3 c = vertices[cPos];
  glm::vec3 ab = glm::normalize((a + b) / 2.0f) * radius;
  glm::vec3 bc = glm::normalize((b + c) / 2.0f) * radius;
  glm::vec3 ac = glm::normalize((a + c) / 2.0f) * radius;
  unsigned int abPos = vertices.size(), bcPos = abPos + 1, acPos = abPos + 2;

  vertices.push_back(ab);
  vertices.push_back(bc);
  vertices.push_back(ac);
  indexData[indicesOffset + 1] = abPos;
  indexData[indicesOffset + 2] = acPos;

  indexData.push_back(acPos);
  indexData.push_back(bcPos);
  indexData.push_back(cPos);

  indexData.push_back(acPos);
  indexData.push_back(abPos);
  indexData.push_back(bcPos);

  indexData.push_back(abPos);
  indexData.push_back(bPos);
  indexData.push_back(bcPos);
}

void SphereMesh::generateVertexData(std::vector<glm::vec3> &vertices) {
  vertexData.reserve(vertices.size() * 8 * 2);
  indexData.reserve(indexData.size() * 2);

  for (auto vertex : vertices)
    addVertexToVertexData(vertex, false);

  // generate lower hemisphere
  for (auto vertex : vertices) {
    vertex.y *= -1;
    addVertexToVertexData(vertex, true);
  }
  int oldIndexDataSize = indexData.size();
  for (int i = 0; i < oldIndexDataSize; i++)
    indexData.push_back(indexData[i] + vertices.size());
}

void SphereMesh::addVertexToVertexData(glm::vec3 vertex, bool offsetTexture) {
  // vertex position
  vertexData.push_back(vertex.x);
  vertexData.push_back(vertex.y);
  vertexData.push_back(vertex.z);
  // vertex normal
  auto normal = glm::normalize(vertex);
  vertexData.push_back(normal.x);
  vertexData.push_back(normal.y);
  vertexData.push_back(normal.z);
  // vertex texture coords
  auto xTexPos = (normal.x / 2.0f + 0.5f) / 2.0f;
  if (offsetTexture)
    xTexPos += 0.5f;
  auto yTexPos = normal.z / 2.0f + 0.5f;
  vertexData.push_back(xTexPos);
  vertexData.push_back(yTexPos);
}
