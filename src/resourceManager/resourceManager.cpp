#include "resourceManager.h"

void ResourceManager::loadTextures(std::vector<std::string> &textureNames) {
  textureManager.load(textureNames);
}

void ResourceManager::loadShaders(std::vector<std::string> &shaderNames) {
  shaderManager.load(shaderNames);
}

int ResourceManager::getTextureID(std::string textureName) {
  return textureManager.getTextureID(textureName);
}

Texture *ResourceManager::getTexture(int textureID) {
  return textureManager.getTexture(textureID);
}

void ResourceManager::useShader(Renderer &renderer, std::string shaderName) {
  shaderManager.useShader(renderer, shaderName);
}

void ResourceManager::toggleShader(Renderer &renderer) {
  shaderManager.toggleShader(renderer);
}
