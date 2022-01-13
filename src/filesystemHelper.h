#pragma once

#include <filesystem>

enum class ResourceType {
  shader,
};

class FilesystemHelper {
private:
  static std::filesystem::path resourcesPath;
  static std::filesystem::path shadersPath;

  static std::filesystem::path fullPathToResourceDir;
public:
  static void init(char* argv0);
  static std::string getResourcePath(ResourceType type,
                                     std::string resource);
};
