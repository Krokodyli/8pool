#include "model.h"
#include <GL/glext.h>

Model::Model(const std::vector<float> &vertices,
             const std::vector<float> &normals) {
  triangleCount = vertices.size() / 3;
  indicesEBO = -1;
  createVAO(vertices, normals);
}

Model::Model(const std::vector<float> &vertices,
             const std::vector<float> &normals,
             const std::vector<unsigned int> &indices) {
  triangleCount = vertices.size() / 3;
  indicesEBO = -1;
  createIndexedVAO(vertices, normals, indices);
}

Model::~Model() {
  glDeleteVertexArrays(1, &modelVAO);
  glDeleteBuffers(1, &verticesVBO);
  glDeleteBuffers(1, &normalsVBO);
  if (indicesEBO >= 0)
    glDeleteBuffers(1, &indicesEBO);
}

void Model::bind() { glBindVertexArray(modelVAO); }
void Model::unbind() { glBindVertexArray(0); }

void Model::createVAO(const std::vector<float> &vertices,
                      const std::vector<float> &normals) {
  generateAndBindVertexArray();
  generateAndBindVertexBuffer(vertices);
  generateAndBindNormalsBuffer(normals);
  unbind();
}

void Model::createIndexedVAO(const std::vector<float> &vertices,
                             const std::vector<float> &normals,
                             const std::vector<unsigned int> &indices) {
  generateAndBindVertexArray();
  generateAndBindVertexBuffer(vertices);
  generateAndBindNormalsBuffer(normals);
  generateAndBindIndicesBuffer(indices);
  unbind();
}

unsigned int Model::getTriangleCount() { return triangleCount; }
bool Model::hasIndexedVertices() { return indicesEBO >= 0; }

void Model::generateAndBindVertexArray() {
  glGenVertexArrays(1, &modelVAO);
  glBindVertexArray(modelVAO);
}

void Model::generateAndBindVertexBuffer(const std::vector<float> &vertices) {
  // generate and bind
  glGenBuffers(1, &verticesVBO);
  glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
  // load data
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0],
               GL_STATIC_DRAW);
  // set VAO attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
}

void Model::generateAndBindNormalsBuffer(const std::vector<float> &normals) {
  // generate and bind
  glGenBuffers(1, &normalsVBO);
  glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
  // load data
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0],
               GL_STATIC_DRAW);
  // set VAO attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
}

void Model::generateAndBindIndicesBuffer(
    const std::vector<unsigned int> &indices) {
  // generate and bind
  glGenBuffers(1, &indicesEBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesEBO);
  // load data
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &indices[0], GL_STATIC_DRAW);
}
