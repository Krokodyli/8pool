#include "model.h"
#include <GL/glext.h>

Model::Model(std::vector<float> &vertices, std::vector<float> &normals) {
  triangleCount = vertices.size() / 3;
  areVerticesIndexed = false;
  createVAO(vertices, normals);
}

Model::Model(std::vector<float> &vertices, std::vector<float> &normals,
             std::vector<unsigned int> &indices) {
  triangleCount = indices.size() / 3;
  areVerticesIndexed = true;
  createIndexedVAO(vertices, normals, indices);
}

Model::~Model() {
  glDeleteVertexArrays(1, &modelVAO);
  glDeleteBuffers(1, &verticesVBO);
  glDeleteBuffers(1, &normalsVBO);
  if (areVerticesIndexed)
    glDeleteBuffers(1, &indicesEBO);
}

unsigned int Model::getID() { return modelVAO; }
void Model::bind() { glBindVertexArray(modelVAO); }
void Model::unbind() { glBindVertexArray(0); }

void Model::createVAO(std::vector<float> &vertices,
                      std::vector<float> &normals) {
  generateAndBindVertexArray();
  generateAndBindVertexBuffer(vertices);
  generateAndBindNormalsBuffer(normals);
  unbind();
}

void Model::createIndexedVAO(std::vector<float> &vertices,
                             std::vector<float> &normals,
                             std::vector<unsigned int> &indices) {
  generateAndBindVertexArray();
  generateAndBindVertexBuffer(vertices);
  generateAndBindNormalsBuffer(normals);
  generateAndBindIndicesBuffer(indices);
  unbind();
}

unsigned int Model::getTriangleCount() { return triangleCount; }
bool Model::hasIndexedVertices() { return areVerticesIndexed; }

void Model::generateAndBindVertexArray() {
  glGenVertexArrays(1, &modelVAO);
  glBindVertexArray(modelVAO);
}

void Model::generateAndBindVertexBuffer(std::vector<float> &vertices) {
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

void Model::generateAndBindNormalsBuffer(std::vector<float> &normals) {
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

void Model::generateAndBindIndicesBuffer(std::vector<unsigned int> &indices) {
  // generate and bind
  glGenBuffers(1, &indicesEBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesEBO);
  // load data
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(),
               &indices[0], GL_STATIC_DRAW);
}
