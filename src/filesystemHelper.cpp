#include "filesystemHelper.h"

std::filesystem::path FilesystemHelper::resourcesPath = "resources/";
std::filesystem::path FilesystemHelper::shadersPath = "shaders/";

std::filesystem::path FilesystemHelper::fullPathToResourceDir = "";

void FilesystemHelper::init(char *argv0) {
  std::filesystem::path execPath = argv0;
  std::filesystem::path cwd = std::filesystem::current_path();
  cwd /= execPath.parent_path();
  cwd = std::filesystem::weakly_canonical(cwd);
  fullPathToResourceDir = cwd / resourcesPath;
  shadersPath = fullPathToResourceDir / shadersPath;
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
