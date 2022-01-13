#include "filesystemHelper.h"

std::filesystem::path FilesystemHelper::resourcesPath = "resources/";
std::filesystem::path FilesystemHelper::shadersPath = "shaders/";

std::filesystem::path FilesystemHelper::fullPathToResourceDir = "";

void FilesystemHelper::init(char *argv0) {
  std::filesystem::path execPath = argv0;
  std::filesystem::path path = std::filesystem::current_path();
  path /= execPath.parent_path();
  path = std::filesystem::weakly_canonical(path);
  fullPathToResourceDir = path / resourcesPath;
  shadersPath = path / shadersPath;
}

std::string FilesystemHelper::getResourcePath(ResourceType type,
                                              std::string resource) {
  if(fullPathToResourceDir == "")
    throw std::runtime_error("Filesystem helper was not initialized");

  switch(type) {
  case ResourceType::shader:
    return shadersPath / resource;
  }

  throw std::runtime_error("Unknown resource type");
}
