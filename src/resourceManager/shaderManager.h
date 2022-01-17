#pragma once

#include "../filesystemHelper.h"
#include "../logger/logger.h"
#include "../shader.h"
#include <string>
#include <unordered_map>
#include <vector>

class Renderer;

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
