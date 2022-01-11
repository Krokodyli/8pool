#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include "../build/_deps/glad-build/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#define INFO_LOG_SIZE 1024

enum class ShaderType { vertex, fragment, program };

class Shader {
private:
  bool isLoaded;
  unsigned int id;
  char errorLog[INFO_LOG_SIZE];

  bool loadSourceCode(std::string filepath, std::string &sourceCode);
  bool compileShader(const std::string &code, unsigned int &id,
                     ShaderType type);
  bool linkShaders(unsigned int vertexShader, unsigned int fragmentShader,
                  unsigned int &shaderProgram);
public:
  Shader();
  ~Shader();

  bool load(std::string vertexShaderPath, std::string fragmentShaderPath);
  void use();
  std::string getError();
  unsigned int getID();

  void bindUniformMat4f(const char *name, const glm::mat4 &mat);
  void bindUniformVec3f(const char *name, const glm::vec3 &mat);
  void bindUniformVec4f(const char *name, const glm::vec4 &mat);
};
