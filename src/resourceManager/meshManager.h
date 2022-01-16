#pragma once

#include "../logger/logger.h"
#include "../model/mesh/mesh.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class MeshManager {
private:
  std::vector<std::unique_ptr<Mesh>> meshes;
  std::unordered_map<std::string, int> nameToResourceID;

public:
  void
  add(std::unordered_map<std::string, std::unique_ptr<Mesh>> &meshesToStore);

  int getMeshID(std::string meshName);
  Mesh &getMesh(int resourceID);
};
