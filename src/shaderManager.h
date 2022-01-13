#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "renderer.h"
#include "shader.h"
#include "filesystemHelper.h"
#include "logger/logger.h"

class ShaderManager {
private:
  std::string vertexShaderPostfix = "_vertex.glsl";
  std::string fragmentShaderPostfix = "_fragment.glsl";

  std::unordered_map<std::string, Shader*> shaders;
  std::string currentShader;

  void loadShader(const std::string &shaderName);
  void dispose();
public:
  ~ShaderManager();
  void load(std::vector<std::string> shadersToLoad,
            Renderer &renderer, bool logCritical = true);

  void useShader(Renderer &renderer, std::string shaderName);
  void toggleShader(Renderer &renderer);
};
