#pragma once

#include <vector>
#include <string>
#include "shaderManager.h"
#include "textureManager.h"

class ResourceManager {
private:
  TextureManager textureManager;
  ShaderManager shaderManager;
public:
  void loadTextures(std::vector<std::string> &textureNames);
  void loadShaders(std::vector<std::string> &shaderNames);

  int getTextureID(std::string textureName);
  Texture *getTexture(int textureID);

  void useShader(Renderer &renderer, std::string shaderName);
  void toggleShader(Renderer &renderer);
};
