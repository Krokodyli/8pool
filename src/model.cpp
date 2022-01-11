#include "model.h"
#include <GL/glext.h>

Model::Model(const std::vector<float> &vertices,
             const std::vector<float> &normals) {
  triangleCount = vertices.size() / 3;
  createVAO(vertices, normals);
}

Model::~Model() {
  glDeleteVertexArrays(1, &vaoID);
  glDeleteBuffers(1, &vbo1ID);
  glDeleteBuffers(1, &vbo2ID);
}

void Model::bind() {
  glBindVertexArray(vaoID);
}

void Model::createVAO(const std::vector<float> &vertices,
                      const std::vector<float> &normals) {
  // generate and bind new VAO
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);
  // generate and bind new VBO for vertices
  glGenBuffers(1, &vbo1ID);
  glBindBuffer(GL_ARRAY_BUFFER, vbo1ID);
  // load data to the vertices VBO
  glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float),
               &vertices[0], GL_STATIC_DRAW);
  // setting VAO vertices attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        (void*)0);
  glEnableVertexAttribArray(0);
  // generate and bind new VBO for normals
  glGenBuffers(1, &vbo2ID);
  // load data to the normals VBO
  glBindBuffer(GL_ARRAY_BUFFER, vbo2ID);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0],
               GL_STATIC_DRAW);
  // setting VAO normals attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  // unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

unsigned int Model::getTriangleCount() {
  return triangleCount;
}
