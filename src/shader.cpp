#include "shader.h"
#include "glm/glm.hpp"
#include <stdexcept>

Shader::Shader() {
  errorLog[0] = 0;
  isLoaded = false;
}

Shader::~Shader() {
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
