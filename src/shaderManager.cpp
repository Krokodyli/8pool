#include "shaderManager.h"

void ShaderManager::load(std::vector<std::string> shadersToLoad) {
  for(const auto& shaderName : shadersToLoad)
    loadShader(shaderName);
}

void ShaderManager::useShader(Renderer &renderer, std::string shaderName) {
  auto shader = shaders.find(shaderName);

  if(shader == shaders.end()) {
    Logger::logError("Trying to use shader that is not loaded");
    return;
  }

  currentShader = shaderName;
  renderer.setShader(shader->second.get());
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

  currentShader = shader->first;
  renderer.setShader(shader->second.get());
}

void ShaderManager::loadShader(const std::string &shaderName) {
  auto newShader = std::make_unique<Shader>();
  auto vertexShaderPath = shaderName + vertexShaderPostfix;
  auto fragmentShaderPath = shaderName + fragmentShaderPostfix;

  vertexShaderPath = FilesystemHelper::getResourcePath(ResourceType::shader,
                                                       vertexShaderPath);
  fragmentShaderPath = FilesystemHelper::getResourcePath(ResourceType::shader,
                                                         fragmentShaderPath);

  auto isShaderLoaded = newShader->load(vertexShaderPath, fragmentShaderPath);

  if (!isShaderLoaded) {
    Logger::logError("Shader \"" + shaderName + "\" could not be loaded");
    Logger::logError(newShader->getError());
    return;
  }

  Logger::log("Shader \"" + shaderName + "\" loaded");
  shaders[shaderName] = std::unique_ptr<Shader>(std::move(newShader));
}
