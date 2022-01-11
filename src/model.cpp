#include "model.h"
#include <GL/glext.h>

Model::Model(const std::vector<float> &vertices) {
  triangleCount = vertices.size() / 3;
  createVAO(vertices);
}

Model::~Model() {
  glDeleteVertexArrays(1, &vaoID);
  glDeleteBuffers(1, &vboID);
}

void Model::bind() {
  glBindVertexArray(vaoID);
}

void Model::createVAO(const std::vector<float> &vertices) {
  // generate and bind new VAO
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);
  // generate and bind new VBO
  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  // load data to the VBO
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float),
               &vertices[0], GL_STATIC_DRAW);
  // setting VAO attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        (void*)0);
  glEnableVertexAttribArray(0);
  // unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

unsigned int Model::getTriangleCount() {
  return triangleCount;
}
