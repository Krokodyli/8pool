#pragma once

#include "../model.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "../logger/logger.h"

class ModelManager {
private:
  std::vector<std::unique_ptr<Model>> models;
  std::unordered_map<std::string, int> nameToResourceID;

public:
  void
  add(std::unordered_map<std::string, std::unique_ptr<Model>> &modelsToStore);

  int getModelID(std::string modelName);
  Model &getModel(int resourceID);
};
