#pragma once

#include "modelManager.h"
#include "shaderManager.h"
#include "textureManager.h"
#include <string>
#include <vector>

class ResourceManager {
private:
  TextureManager textureManager;
  ShaderManager shaderManager;
  ModelManager modelManager;

public:
  void addModels(
      std::unordered_map<std::string, std::unique_ptr<Model>> &modelsToStore);

  int getModelID(std::string modelName);
  Model &getModel(int resourceID);

  void loadTextures(std::vector<std::string> &textureNames);
  void loadShaders(std::vector<std::string> &shaderNames);

  int getTextureID(std::string textureName);
  Texture &getTexture(int textureID);

  void useShader(Renderer &renderer, std::string shaderName);
  void toggleShader(Renderer &renderer);
};
