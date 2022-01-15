#pragma once

#include <filesystem>

enum class ResourceType {
  shader,
  texture,
};

class FilesystemHelper {
private:
  static std::filesystem::path shadersPath;
  static std::filesystem::path texturesPath;
  static bool initialized;

public:
  static void init(char *argv0);
  static std::string getResourcePath(ResourceType type, std::string& resource);
};
