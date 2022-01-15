#include "cuboidMesh.h"
#include <string>
#include "../logger/logger.h"

CuboidMesh::CuboidMesh(float xSize, float ySize, float zSize) {
  generateMesh(xSize, ySize, zSize);
}

Model CuboidMesh::generateModel() {
  return Model(vertexData);
}

void CuboidMesh::generateMesh(float xSize, float ySize, float zSize) {
  vertexData.reserve(36 * 8);

  for (int side = 0; side < 6; side++) {
    // detect surface
    int offset = side * 2 * 3 * 3;
    glm::vec3 vertices[3];
    int changingCoord1, changingCoord2;
    int constCoord;
    for (int i = 0; i < 3; i++)
      vertices[i] = {data[offset + i * 3], data[offset + i * 3 + 1],
                     data[offset + i * 3 + 2]};
    for(int coord = 0; coord < 3; coord++) {
      if(vertices[0][coord] == vertices[1][coord] &&
         vertices[1][coord] == vertices[2][coord]) {
        constCoord = coord;
        changingCoord1 = (coord+1)%3;
        changingCoord2 = (coord + 2) % 3;
      }
    }

    // calculate normal
    glm::vec3 normal = { 0.0f, 0.0f, 0.0f };
    normal[constCoord] = vertices[0][constCoord] * 2.0f;

    for(int vertex = 0; vertex < 6; vertex++) {
      // push position
      vertexData.push_back(data[offset + vertex * 3] * xSize);
      vertexData.push_back(data[offset + vertex * 3 + 1] * ySize);
      vertexData.push_back(data[offset + vertex * 3 + 2] * zSize);
      // push normal
      for(int i = 0; i < 3; i++)
        vertexData.push_back(normal[i]);
      // push texture coordinates
      float xOffset = 1.0f / 3.0f * (side % 3);
      int ySide = (side / 3);
      float yOffset = 0.50f * ySide;
      auto xCoord = data[offset + vertex * 3 + changingCoord1];
      auto yCoord = data[offset + vertex * 3 + changingCoord2];
      xCoord = (xCoord + 0.5f) / 3.0f;
      yCoord = (yCoord + 0.5f) / 2.0f;
      vertexData.push_back(xCoord + xOffset);
      vertexData.push_back(yCoord + yOffset);
    }
  }
}
