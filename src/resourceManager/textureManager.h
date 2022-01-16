#pragma once

#include <unordered_map>
#include <vector>
#include "../filesystemHelper.h"
#include "../logger/logger.h"
#include "../model/texture/texture.h"

class TextureManager {
private:
  std::vector<std::unique_ptr<Texture>> textures;
  std::unordered_map<std::string, int> nameToResourceID;

  void loadTexture(std::string &textureName);
public:
  void load(std::vector<std::string> &texturesToLoad);

  int getTextureID(std::string textureName);
  Texture &getTexture(int resourceID);
};
