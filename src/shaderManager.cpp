#include "shaderManager.h"

ShaderManager::~ShaderManager() {
  dispose();
}

void ShaderManager::load(std::vector<std::string> shadersToLoad,
                         Renderer &renderer, bool logCritical) {
  dispose();

  for(const auto& shaderName : shadersToLoad)
    loadShader(shaderName);

  if(shaders.size() == 0) {
    LogType logType = logCritical ? LogType::criticalError : LogType::error;
    Logger::log("No shaders were loaded", logType);
    return;
  }

  currentShader = shaders.begin()->first;
  renderer.setShader(shaders.begin()->second);
}

void ShaderManager::useShader(Renderer &renderer, std::string shaderName) {
  auto shader = shaders.find(shaderName);

  if(shader == shaders.end()) {
    Logger::logError("Trying to use shader that is not loaded");
    return;
  }

  currentShader = shaderName;
  renderer.setShader(shader->second);
}

void ShaderManager::toggleShader(Renderer &renderer) {
  auto shader = shaders.find(currentShader);

  if(shader == shaders.end()) {
    Logger::logError("Shaders were not loaded. Could not toggle shader.");
    return;
  }

  shader._M_incr();
  if(shader == shaders.end())
    shader = shaders.begin();

  renderer.setShader(shader->second);
  currentShader = shader->first;
}

void ShaderManager::loadShader(const std::string &shaderName) {
  Shader *newShader = new Shader();
  std::string vertexShaderPath = shaderName + vertexShaderPostfix;
  std::string fragmentShaderPath = shaderName + fragmentShaderPostfix;
  vertexShaderPath = FilesystemHelper::getResourcePath(ResourceType::shader,
                                                       vertexShaderPath);
  fragmentShaderPath = FilesystemHelper::getResourcePath(ResourceType::shader,
                                                         fragmentShaderPath);
  bool isShaderLoaded = newShader->load(vertexShaderPath, fragmentShaderPath);

  if (!isShaderLoaded) {
    Logger::logError("Shader \"" + shaderName + "\" could not be loaded");
    Logger::logError(newShader->getError());
    delete newShader;
    return;
  }

  Logger::log("Shader \"" + shaderName + "\" loaded");
  shaders[shaderName] = newShader;
}

void ShaderManager::dispose() {
  for(auto &entry : shaders)
    delete entry.second;

  shaders.clear();
  currentShader = "";
}
