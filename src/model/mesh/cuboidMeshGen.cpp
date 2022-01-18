#include "cuboidMeshGen.h"

CuboidMeshGenerator::CuboidMeshGenerator(float xSize, float ySize,
                                         float zSize) {
  generateMesh(xSize, ySize, zSize);
}

std::unique_ptr<Mesh> CuboidMeshGenerator::getMesh() {
  return std::make_unique<Mesh>(vertexData);
}

void CuboidMeshGenerator::generateMesh(float xSize, float ySize, float zSize) {
  int sideOffset = 48;
  vertexData.reserve(sideOffset * 6);

  for (int side = 0; side < 6; side++) {
    // calculate normal
    int constCoord = side % 3;
    bool negative = (side % 2 == 0);
    auto normal = glm::vec3(0.0f);
    normal[constCoord] = 1.0f * (negative ? -1 : 1);

    // calculate cube coords
    int coord1 = (constCoord + 1) % 3;
    int coord2 = (constCoord + 2) % 3;
    glm::vec3 vertices[4];
    for (int j = 0; j < 4; j++) {
      vertices[j][constCoord] = 0.5f * (negative ? -1 : 1);
      vertices[j][coord1] = 0.5f * (j % 2 == 0 ? 1 : -1);
      vertices[j][coord2] = 0.5f * (j / 2 == 0 ? 1 : -1);
    }

    // calculate texture coords
    glm::vec2 texCoords[4];
    float xOffset = (int)(side%3) * 1.0f / 3.0f;
    float yOffset = (int)(side/3) * 0.5f;
    for(int j = 0; j < 4; j++) {
      texCoords[j][0] = (vertices[j][coord1]+0.5f) / 3.0f + xOffset;
      texCoords[j][1] = (vertices[j][coord2]+0.5f) / 2.0f + yOffset;
    }

    // vertices in triangles have to be in clockwise order
    if(!negative) {
      unsigned int triangles[2][3] = {{0, 1, 3}, {0, 3, 2}};
      for (int i = 0; i < 2; i++)
        addTriangleToVertexData(vertices, normal, texCoords, triangles[i]);
    }
    else {
      unsigned int triangles[2][3] = {{3, 1, 0}, {2, 3, 0}};
      for (int i = 0; i < 2; i++)
        addTriangleToVertexData(vertices, normal, texCoords, triangles[i]);
    }
  }

  // apply scale
  for(int i = 0; i < vertexData.size(); i += 8) {
    vertexData[i] *= xSize;
    vertexData[i+1] *= ySize;
    vertexData[i+2] *= zSize;
  }
}

void CuboidMeshGenerator::addTriangleToVertexData(glm::vec3 vertices[4],
                                                  glm::vec3 normal,
                                                  glm::vec2 texCoords[4],
                                                  unsigned int indices[3]) {
  for(int i = 0; i < 3; i++) {
    int index = indices[i];
    vertexData.push_back(vertices[index].x);
    vertexData.push_back(vertices[index].y);
    vertexData.push_back(vertices[index].z);
    vertexData.push_back(normal.x);
    vertexData.push_back(normal.y);
    vertexData.push_back(normal.z);
    vertexData.push_back(texCoords[index].x);
    vertexData.push_back(texCoords[index].y);
  }
}
