#include "sphereMesh.h"

SphereMesh::SphereMesh(float radius, unsigned int precision)
    : radius(radius), precision(precision) {
  generateMesh();
}

Model SphereMesh::generateModel() {
  return Model(verticesF, normalsF, indices);
}

void SphereMesh::generateMesh() {
  std::vector<glm::vec3> vertices;
  generateInitialMesh(vertices);
  for (int i = 0; i < precision; i++) {
    unsigned int triangleOffset = 0;
    unsigned int oldIndicesListSize = indices.size();
    for (; triangleOffset < oldIndicesListSize; triangleOffset += 3)
      divideTriangle(vertices, triangleOffset);
  }
  generateFloatVertices(vertices);
  generateFloatNormals(vertices);
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
      indices.push_back(i + 2);
      indices.push_back(j + 2);
      indices.push_back(top);
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
  unsigned int aPos = indices[indicesOffset];
  unsigned int bPos = indices[indicesOffset + 1];
  unsigned int cPos = indices[indicesOffset + 2];
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
  indices[indicesOffset + 1] = abPos;
  indices[indicesOffset + 2] = acPos;

  indices.push_back(acPos);
  indices.push_back(bcPos);
  indices.push_back(cPos);

  indices.push_back(acPos);
  indices.push_back(abPos);
  indices.push_back(bcPos);

  indices.push_back(abPos);
  indices.push_back(bPos);
  indices.push_back(bcPos);
}

void SphereMesh::generateFloatVertices(std::vector<glm::vec3> &vertices) {
  verticesF.reserve(vertices.size() * 3);
  for (auto &vertex : vertices) {
    verticesF.push_back(vertex.x);
    verticesF.push_back(vertex.y);
    verticesF.push_back(vertex.z);
  }
}

void SphereMesh::generateFloatNormals(std::vector<glm::vec3> &vertices) {
  normalsF.reserve(vertices.size() * 3);
  for (auto &vertex : vertices) {
    auto normalized = glm::normalize(vertex);
    normalsF.push_back(normalized.x);
    normalsF.push_back(normalized.y);
    normalsF.push_back(normalized.z);
  }
}
