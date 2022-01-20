#pragma once

#include "includes/glad.h"
#include "includes/glm.h"
#include "light/light.h"
#include "model/modelMaterial.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define INFO_LOG_SIZE 1024

#define SHAD_NR_LIGHTS 5
#define SHAD_LIGHT_SECTION_BEGIN 13
#define SHAD_LIGHT_SECTION_LEN 8
#define SHAD_LOCATIONS_ARR_SIZE 53

#define SHAD_LOC_OBJ_TYPE 0
#define SHAD_LOC_MODEL_MAT 1
#define SHAD_LOC_NORMAL_MAT 2
#define SHAD_LOC_COLOR 3

#define SHAD_LOC_VIEW_MAT 4
#define SHAD_LOC_PROJECTION_MAT 5
#define SHAD_LOC_VIEW_POS 6

#define SHAD_LOC_MAT_AMBIENT 7
#define SHAD_LOC_MAT_DIFFUSE 8
#define SHAD_LOC_MAT_SPECULAR 9
#define SHAD_LOC_MAT_SHININESS 10

#define SHAD_LOC_FOG_FACTOR 11
#define SHAD_LOC_FOG_COLOR 12

#define SHAD_LIGHT_TYPE 0
#define SHAD_LIGHT_POS 1
#define SHAD_LIGHT_DIR 2
#define SHAD_LIGHT_CUTOFF 3
#define SHAD_LIGHT_ATTENUATION 4
#define SHAD_LIGHT_AMBIENT 5
#define SHAD_LIGHT_DIFFUSE 6
#define SHAD_LIGHT_SPECULAR 7

enum class ShaderType { vertex, fragment, program };

class Shader {
private:
  static constexpr int maxLightSources = 5;

  bool isLoaded;
  unsigned int id;
  char errorLog[INFO_LOG_SIZE];
  unsigned int locations[SHAD_LOCATIONS_ARR_SIZE];

  bool loadSourceCode(std::string filepath, std::string &sourceCode);
  bool compileShader(const std::string &code, unsigned int &id,
                     ShaderType type);
  bool linkShaders(unsigned int vertexShader, unsigned int fragmentShader,
                   unsigned int &shaderProgram);
  void generateLocations();

public:
  Shader();
  Shader(const Shader &r) = delete;
  ~Shader();

  bool load(std::string vertexShaderPath, std::string fragmentShaderPath);
  void use();
  std::string getError();
  unsigned int getID();

  void bindUniformMat3f(unsigned int location, const glm::mat3 &mat);
  void bindUniformMat4f(unsigned int location, const glm::mat4 &mat);
  void bindUniformVec2f(unsigned int location, const glm::vec2 &mat);
  void bindUniformVec3f(unsigned int location, const glm::vec3 &mat);
  void bindUniformVec4f(unsigned int location, const glm::vec4 &mat);
  void bindUniformFloat(unsigned int location, float value);
  void bindUniformUint(unsigned int location, unsigned int value);

  void bindMaterial(ModelMaterial &material);
  void bindLights(std::vector<Light *> &lights);
};
