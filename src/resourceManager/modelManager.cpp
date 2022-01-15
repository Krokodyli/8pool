#include "modelManager.h"

void ModelManager::add(
    std::unordered_map<std::string, std::unique_ptr<Model>> &modelsToStore) {
  for(auto &modelToStore : modelsToStore) {
    nameToResourceID[modelToStore.first] = models.size();
    models.push_back(std::move(modelToStore.second));
  };
}

int ModelManager::getModelID(std::string modelName) {
  auto model = nameToResourceID.find(modelName);

  if (model == nameToResourceID.end()) {
    Logger::logCriticalError("Could not get texture ID");
    return -1;
  } else {
    return model->second;
  }
}

Model &ModelManager::getModel(int resourceID) {
  if (resourceID < 0 || resourceID >= models.size())
    Logger::logCriticalError("Could not get model. Invalid resource ID");

  return *models[resourceID];
}
