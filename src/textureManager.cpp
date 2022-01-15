#include "textureManager.h"

void TextureManager::load(std::vector<std::string> texturesToLoad) {
  for(auto &textureName : texturesToLoad)
    loadTexture(textureName);

}

void TextureManager::loadTexture(std::string &textureName) {
  auto newTexture = std::make_unique<Texture>();
  auto texturePath = FilesystemHelper::getResourcePath(ResourceType::texture,
                                                       textureName);
  auto isLoaded = newTexture->load(texturePath);

  if(!isLoaded) {
    Logger::logError("Texture \"" + textureName + "\" could not be loaded");
    return;
  }

  int textureID = textures.size();
  textures.push_back(std::move(newTexture));
  nameToResourceID[textureName] = textureID;
  Logger::log("Texture \"" + textureName + "\" loaded");
}

int TextureManager::getTextureID(std::string textureName) {
  auto texture = nameToResourceID.find(textureName);

  if(texture == nameToResourceID.end()) {
    Logger::logCriticalError("Could not get texture ID");
    return -1;
  }
  else {
    return texture->second;
  }
}

Texture *TextureManager::getTexture(int resourceID) {
  if(resourceID < 0 || resourceID >= textures.size()) {
    Logger::logCriticalError("Could not get texture. Invalid resource ID");
    return nullptr;
  }
  else {
    return textures[resourceID].get();
  }
}
