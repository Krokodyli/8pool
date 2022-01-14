#include "model.h"
#include <GL/glext.h>

Model::Model(std::vector<float> &vertexData) {
  triangleCount = vertexData.size() / 8;
  areVerticesIndexed = false;
  createVAO(vertexData);
}

Model::Model(std::vector<float> &vertexData,
             std::vector<unsigned int> &indexData) {
  triangleCount = indexData.size() / 3;
  areVerticesIndexed = true;
  createIndexedVAO(vertexData, indexData);
}

Model::~Model() {
  glDeleteVertexArrays(1, &vao);
  if (areVerticesIndexed)
    glDeleteBuffers(1, &ebo);
}

unsigned int Model::getID() { return vao; }
void Model::bind() { glBindVertexArray(vao); }
void Model::unbind() { glBindVertexArray(0); }

void Model::createVAO(std::vector<float> &vertexData) {
  generateAndBindVertexArray();
  generateAndBindVertexBuffer();
  loadVertexData(vertexData);
  setUpVertexAttributes();
  unbind();
}

void Model::createIndexedVAO(std::vector<float> &vertexData,
                             std::vector<unsigned int> &indexData) {
  generateAndBindVertexArray();
  generateAndBindVertexBuffer();
  loadVertexData(vertexData);
  generateAndBindElementArray();
  loadIndexData(indexData);
  setUpVertexAttributes();
  unbind();
}

unsigned int Model::getTriangleCount() { return triangleCount; }
bool Model::hasIndexedVertices() { return areVerticesIndexed; }

void Model::generateAndBindVertexArray() {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
}

void Model::generateAndBindVertexBuffer() {
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Model::loadVertexData(std::vector<float> &vertexData) {
  glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float),
               &vertexData[0], GL_STATIC_DRAW);
}

void Model::setUpVertexAttributes() {
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

void Model::generateAndBindElementArray() {
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void Model::loadIndexData(std::vector<unsigned int> &indexData) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int),
               &indexData[0], GL_STATIC_DRAW);
}
