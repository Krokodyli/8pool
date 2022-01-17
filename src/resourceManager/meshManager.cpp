#include "meshManager.h"

void MeshManager::add(
    std::unordered_map<std::string, std::unique_ptr<Mesh>> &meshesToStore) {
  for (auto &meshToStore : meshesToStore) {
    nameToResourceID[meshToStore.first] = meshes.size();
    meshes.push_back(std::move(meshToStore.second));
  };
}

int MeshManager::getMeshID(std::string meshName) {
  auto mesh = nameToResourceID.find(meshName);

  if (mesh == nameToResourceID.end()) {
    Logger::logCriticalError("Could not get mesh ID");
    return -1;
  } else {
    return mesh->second;
  }
}

Mesh &MeshManager::getMesh(int resourceID) {
  if (resourceID < 0 || resourceID >= meshes.size())
    Logger::logCriticalError("Could not get mesh. Invalid resource ID");

  return *meshes[resourceID];
}
