#pragma once

#include "meshManager.h"
#include "shaderManager.h"
#include "textureManager.h"
#include <string>
#include <vector>

class ResourceManager {
private:
  TextureManager textureManager;
  ShaderManager shaderManager;
  MeshManager meshManager;

public:
  void addMeshes(
      std::unordered_map<std::string, std::unique_ptr<Mesh>> &meshesToStore);

  int getMeshID(std::string meshName);
  Mesh &getMesh(int resourceID);

  void loadTextures(std::vector<std::string> &textureNames);
  void loadShaders(std::vector<std::string> &shaderNames);

  int getTextureID(std::string textureName);
  Texture &getTexture(int textureID);

  void useShader(Renderer &renderer, std::string shaderName);
  void toggleShader(Renderer &renderer);
};
