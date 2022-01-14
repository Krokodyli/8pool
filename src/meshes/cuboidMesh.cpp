#include "cuboidMesh.h"

CuboidMesh::CuboidMesh(float xSize, float ySize, float zSize)
    : xSize(xSize), ySize(ySize), zSize(zSize) {
  generateMesh();
}

Model CuboidMesh::generateModel() {
  return Model(vertices, normals);
}

void CuboidMesh::generateMesh() {
  vertices.reserve(cubeModelDataLen / 2);
  normals.reserve(cubeModelDataLen / 2);

  for (int i = 0; i < cubeModelDataLen; i += 6) {
    float xPos = xSize * cubeModelData[i];
    vertices.push_back(xPos);
    float yPos = ySize * cubeModelData[i + 1];
    vertices.push_back(yPos);
    float zPos = zSize * cubeModelData[i + 2];
    vertices.push_back(zPos);

    normals.push_back(cubeModelData[i + 3]);
    normals.push_back(cubeModelData[i + 4]);
    normals.push_back(cubeModelData[i + 5]);
  }
}
