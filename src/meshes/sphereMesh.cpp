#include "sphereMesh.h"

SphereMesh::SphereMesh(float radius, unsigned int precision)
    : radius(radius), precision(precision) {
  generateMesh();
}

Model SphereMesh::generateModel() {
  return Model(vertexData, indexData);
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
  vertices.push_back({0.0f, r, 0.0f});
  vertices.push_back({0.0f, -r, 0.0f});
  vertices.push_back({r2, 0.0f, -r2});
  vertices.push_back({r2, 0.0f, r2});
  vertices.push_back({-r2, 0.0f, r2});
  vertices.push_back({-r2, 0.0f, -r2});
  for (int i = 0; i < 4; i++) {
    int j = (i + 1) % 4;
    for (int top = 0; top < 2; top++) {
      indexData.push_back(i + 2);
      indexData.push_back(j + 2);
      indexData.push_back(top);
    }
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
  vertexData.reserve(vertices.size() * 3);
  for (auto &vertex : vertices) {
    // vertex position
    vertexData.push_back(vertex.x);
    vertexData.push_back(vertex.y);
    vertexData.push_back(vertex.z);
    // vertex normal
    auto normalized = glm::normalize(vertex);
    vertexData.push_back(normalized.x);
    vertexData.push_back(normalized.y);
    vertexData.push_back(normalized.z);
    // vertex texture coords
    vertexData.push_back(0.0f);
    vertexData.push_back(0.0f);
  }
}
