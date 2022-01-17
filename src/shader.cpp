#include "shader.h"

Shader::Shader() {
  errorLog[0] = 0;
  isLoaded = false;
}

Shader::~Shader() {
  glUseProgram(0);
  if(isLoaded)
    glDeleteProgram(id);
}

bool Shader::load(std::string vertexShaderPath,
                  std::string fragmentShaderPath) {
  std::string vShaderSrc, fShaderSrc;

  if(!loadSourceCode(vertexShaderPath, vShaderSrc))
    return false;
  if(!loadSourceCode(fragmentShaderPath, fShaderSrc))
    return false;

  unsigned int vShader, fShader, shaderProgram;

  if(!compileShader(vShaderSrc, vShader, ShaderType::vertex))
     return false;
  if (!compileShader(fShaderSrc, fShader, ShaderType::fragment)) {
    glDeleteShader(vShader);
    return false;
  }

  bool success = linkShaders(vShader, fShader, shaderProgram);

  glDeleteShader(vShader);
  glDeleteShader(fShader);

  if(success) {
    id = shaderProgram;
    isLoaded = true;
  }

  return success;
}

void Shader::use() {
  if(isLoaded)
    glUseProgram(id);
  else
    throw std::runtime_error("Trying to use uninitialized shader");
}

std::string Shader::getError() {
  return std::string(errorLog);
}

unsigned int Shader::getID() {
  return id;
}

void Shader::bindUniformMat4f(const char *name, const glm::mat4 &mat) {
  unsigned int location = glGetUniformLocation(id, name);
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::bindUniformVec2f(const char *name, const glm::vec2 &vec) {
  unsigned int location = glGetUniformLocation(id, name);
  glUniform2f(location, vec.x, vec.y);
}

void Shader::bindUniformVec3f(const char *name, const glm::vec3 &vec) {
  unsigned int location = glGetUniformLocation(id, name);
  glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::bindUniformVec4f(const char *name, const glm::vec4 &vec) {
  unsigned int location = glGetUniformLocation(id, name);
  glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Shader::bindUniformFloat(const char *name, float value) {
  unsigned int location = glGetUniformLocation(id, name);
  glUniform1f(location, value);
}

void Shader::bindUniformUint(const char *name, unsigned int value) {
  unsigned int location = glGetUniformLocation(id, name);
  glUniform1ui(location, value);
}

void Shader::bindMaterial(ModelMaterial &material) {
  bindUniformVec3f("material.ambient", material.ambient);
  bindUniformVec3f("material.diffuse", material.diffuse);
  bindUniformVec3f("material.specular", material.specular);
  bindUniformFloat("material.shininess", material.shininess);
}

void Shader::bindLights(std::vector<Light *> &lights) {
  int i;
  for(i = 0; i < lights.size() && i < maxLightSources; i++) {
    auto lightLabel = "lights[" + std::to_string(i) + "]";
    auto typeLabel = lightLabel + ".type";
    bindUniformUint(typeLabel.c_str(), (unsigned int)lights[i]->lightType);
    auto posLabel = lightLabel + ".position";
    bindUniformVec3f(posLabel.c_str(), lights[i]->position);
    auto dirLabel = lightLabel + ".direction";
    bindUniformVec3f(posLabel.c_str(), lights[i]->direction);
    auto cutOffLabel = lightLabel + ".cutOff";
    bindUniformVec2f(cutOffLabel.c_str(), lights[i]->cutOff);
    auto attenuationLabel = lightLabel + ".attenuation";
    bindUniformVec3f(posLabel.c_str(), lights[i]->attenuation);
    auto ambient = lightLabel + ".ambient";
    bindUniformVec3f(posLabel.c_str(), lights[i]->attenuation);
    auto diffuse = lightLabel + ".diffuse";
    bindUniformVec3f(posLabel.c_str(), lights[i]->diffuse);
    auto specular = lightLabel + ".specular";
    bindUniformVec3f(posLabel.c_str(), lights[i]->specular);
  }
  for(; i < maxLightSources; i++) {
    auto lightLabel = "lights[" + std::to_string(i) + "]";
    auto typeLabel = lightLabel + ".type";
    bindUniformUint(typeLabel.c_str(), 0);
  }
}

bool Shader::linkShaders(unsigned int vertexShader, unsigned int fragmentShader,
                         unsigned int &shaderProgram) {
  shaderProgram = glCreateProgram();
  if(shaderProgram == 0)
    return false;

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(shaderProgram, INFO_LOG_SIZE, NULL, errorLog);
    glDeleteProgram(shaderProgram);
    return false;
  }

  return true;
}

bool Shader::compileShader(const std::string &code, unsigned int &sid,
                           ShaderType type) {
  if(type == ShaderType::vertex)
    sid = glCreateShader(GL_VERTEX_SHADER);
  else if(type == ShaderType::fragment)
    sid = glCreateShader(GL_FRAGMENT_SHADER);
  else
    return false;

  const char *cCode = code.c_str();
  glShaderSource(sid, 1, &cCode, NULL);
  glCompileShader(sid);

  int success;
  glGetShaderiv(sid, GL_COMPILE_STATUS, &success);

  if(!success) {
    glGetShaderInfoLog(sid, INFO_LOG_SIZE, NULL, errorLog);
    glDeleteShader(sid);
    return false;
  }

  return true;
}

bool Shader::loadSourceCode(std::string filepath, std::string &sourceCode) {
  std::ifstream file;
  file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
  try {
    file.open(filepath);
    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    sourceCode = stream.str();
  } catch(std::ifstream::failure &exception) {
    return false;
  }
  return true;
}
