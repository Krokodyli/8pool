#include "mesh.h"
#include "../../includes/glad.h"

Mesh::Mesh(std::vector<float> &vertexData) {
  triangleCount = vertexData.size() / 8;
  areVerticesIndexed = false;
  createVAO(vertexData);
}

Mesh::Mesh(std::vector<float> &vertexData,
           std::vector<unsigned int> &indexData) {
  triangleCount = indexData.size() / 3;
  areVerticesIndexed = true;
  createIndexedVAO(vertexData, indexData);
}

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &vao);
  if (areVerticesIndexed)
    glDeleteBuffers(1, &ebo);
}

unsigned int Mesh::getID() { return vao; }
void Mesh::bind() { glBindVertexArray(vao); }
void Mesh::unbind() { glBindVertexArray(0); }

void Mesh::createVAO(std::vector<float> &vertexData) {
  generateAndBindVertexArray();
  generateAndBindVertexBuffer();
  loadVertexData(vertexData);
  setUpVertexAttributes();
  unbind();
}

void Mesh::createIndexedVAO(std::vector<float> &vertexData,
                            std::vector<unsigned int> &indexData) {
  generateAndBindVertexArray();
  generateAndBindVertexBuffer();
  loadVertexData(vertexData);
  generateAndBindElementArray();
  loadIndexData(indexData);
  setUpVertexAttributes();
  unbind();
}

unsigned int Mesh::getTriangleCount() { return triangleCount; }
bool Mesh::hasIndexedVertices() { return areVerticesIndexed; }

void Mesh::generateAndBindVertexArray() {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
}

void Mesh::generateAndBindVertexBuffer() {
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Mesh::loadVertexData(std::vector<float> &vertexData) {
  glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float),
               &vertexData[0], GL_STATIC_DRAW);
}

void Mesh::setUpVertexAttributes() {
  // vertex position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // vertex normal
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // vertex texture coords
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
}

void Mesh::generateAndBindElementArray() {
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void Mesh::loadIndexData(std::vector<unsigned int> &indexData) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int),
               &indexData[0], GL_STATIC_DRAW);
}
