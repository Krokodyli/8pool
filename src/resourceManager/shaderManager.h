#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "../renderer.h"
#include "../shader.h"
#include "../filesystemHelper.h"
#include "../logger/logger.h"

class ShaderManager {
private:
  std::string vertexShaderPostfix = "_vertex.glsl";
  std::string fragmentShaderPostfix = "_fragment.glsl";

  std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
  std::string currentShader;

  void loadShader(std::string &shaderName);
public:
  void load(std::vector<std::string> &shadersToLoad);

  void useShader(Renderer &renderer, std::string shaderName);
  void toggleShader(Renderer &renderer);
};
