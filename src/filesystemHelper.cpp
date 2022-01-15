#include "filesystemHelper.h"

std::filesystem::path FilesystemHelper::shadersPath = "shaders/";
std::filesystem::path FilesystemHelper::texturesPath = "textures/";
bool FilesystemHelper::initialized = false;

void FilesystemHelper::init(char *argv0) {
  std::filesystem::path execPath = argv0;
  std::filesystem::path path = std::filesystem::current_path();
  path /= execPath.parent_path();
  path = std::filesystem::weakly_canonical(path);
  shadersPath = path / shadersPath;
  texturesPath = path / texturesPath;
  initialized = true;
}

std::string FilesystemHelper::getResourcePath(ResourceType type,
                                              std::string& resource) {
  if (!initialized)
    throw std::runtime_error("Filesystem helper was not initialized");

  switch (type) {
  case ResourceType::shader:
    return shadersPath / resource;
  case ResourceType::texture:
    return texturesPath / resource;
  }

  throw std::runtime_error("Unknown resource type");
}
