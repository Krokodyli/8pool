#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include "../build/_deps/glad-build/include/glad/glad.h"
#include <GLFW/glfw3.h>

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
};
