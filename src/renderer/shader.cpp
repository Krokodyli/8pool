#include "../renderer/shader.h"
#include <unordered_map>

Shader::Shader() {
  errorLog[0] = 0;
  isLoaded = false;
}

Shader::~Shader() {
  glUseProgram(0);
  if (isLoaded)
    glDeleteProgram(id);
}

bool Shader::load(std::string vertexShaderPath,
                  std::string fragmentShaderPath) {
  std::string vShaderSrc, fShaderSrc;

  if (!loadSourceCode(vertexShaderPath, vShaderSrc))
    return false;
  if (!loadSourceCode(fragmentShaderPath, fShaderSrc))
    return false;

  unsigned int vShader, fShader, shaderProgram;

  if (!compileShader(vShaderSrc, vShader, ShaderType::vertex))
    return false;
  if (!compileShader(fShaderSrc, fShader, ShaderType::fragment)) {
    glDeleteShader(vShader);
    return false;
  }

  bool success = linkShaders(vShader, fShader, shaderProgram);

  glDeleteShader(vShader);
  glDeleteShader(fShader);

  if (success) {
    id = shaderProgram;
    isLoaded = true;
  }

  generateLocations();

  return success;
}

void Shader::use() {
  if (isLoaded)
    glUseProgram(id);
  else
    throw std::runtime_error("Trying to use uninitialized shader");
}

std::string Shader::getError() { return std::string(errorLog); }

unsigned int Shader::getID() { return id; }

void Shader::bindUniformMat3f(unsigned int location, const glm::mat3 &mat) {
  glUniformMatrix3fv(locations[location], 1, GL_FALSE, glm::value_ptr(mat));
}
void Shader::bindUniformMat4f(unsigned int location, const glm::mat4 &mat) {
  glUniformMatrix4fv(locations[location], 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::bindUniformVec2f(unsigned int location, const glm::vec2 &vec) {
  glUniform2f(locations[location], vec.x, vec.y);
}

void Shader::bindUniformVec3f(unsigned int location, const glm::vec3 &vec) {
  glUniform3f(locations[location], vec.x, vec.y, vec.z);
}

void Shader::bindUniformVec4f(unsigned int location, const glm::vec4 &vec) {
  glUniform4f(locations[location], vec.x, vec.y, vec.z, vec.w);
}

void Shader::bindUniformFloat(unsigned int location, float value) {
  glUniform1f(locations[location], value);
}

void Shader::bindUniformUint(unsigned int location, unsigned int value) {
  glUniform1ui(locations[location], value);
}

void Shader::bindMaterial(ModelMaterial &material) {
  glUniform3fv(locations[SHAD_LOC_MAT_AMBIENT], 1,
               glm::value_ptr(material.ambient));

  glUniform3fv(locations[SHAD_LOC_MAT_DIFFUSE], 1,
               glm::value_ptr(material.diffuse));

  glUniform3fv(locations[SHAD_LOC_MAT_SPECULAR], 1,
               glm::value_ptr(material.specular));

  glUniform1f(locations[SHAD_LOC_MAT_SHININESS], material.shininess);
}

void Shader::bindLights(std::vector<Light *> &lights) {
  int i;
  for (i = 0; i < lights.size() && i < maxLightSources; i++) {
    int offset = SHAD_LIGHT_SECTION_BEGIN + i * SHAD_LIGHT_SECTION_LEN;
    glUniform1ui(locations[offset + SHAD_LIGHT_TYPE],
                 (unsigned int)lights[i]->lightType);
    glUniform3fv(locations[offset + SHAD_LIGHT_POS], 1,
                 glm::value_ptr(lights[i]->position));
    glUniform3fv(locations[offset + SHAD_LIGHT_DIR], 1,
                 glm::value_ptr(lights[i]->direction));
    glUniform2fv(locations[offset + SHAD_LIGHT_CUTOFF], 1,
                 glm::value_ptr(lights[i]->cutOff));
    glUniform3fv(locations[offset + SHAD_LIGHT_ATTENUATION], 1,
                 glm::value_ptr(lights[i]->attenuation));
    glUniform3fv(locations[offset + SHAD_LIGHT_AMBIENT], 1,
                 glm::value_ptr(lights[i]->ambient));
    glUniform3fv(locations[offset + SHAD_LIGHT_DIFFUSE], 1,
                 glm::value_ptr(lights[i]->diffuse));
    glUniform3fv(locations[offset + SHAD_LIGHT_SPECULAR], 1,
                 glm::value_ptr(lights[i]->specular));
  }

  for (; i < maxLightSources; i++) {
    int offset = SHAD_LIGHT_SECTION_BEGIN + i * SHAD_LIGHT_SECTION_LEN;
    glUniform1ui(locations[offset + SHAD_LIGHT_TYPE], 0);
  }
}

bool Shader::linkShaders(unsigned int vertexShader, unsigned int fragmentShader,
                         unsigned int &shaderProgram) {
  shaderProgram = glCreateProgram();
  if (shaderProgram == 0)
    return false;

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, INFO_LOG_SIZE, NULL, errorLog);
    glDeleteProgram(shaderProgram);
    return false;
  }

  return true;
}

bool Shader::compileShader(const std::string &code, unsigned int &sid,
                           ShaderType type) {
  if (type == ShaderType::vertex)
    sid = glCreateShader(GL_VERTEX_SHADER);
  else if (type == ShaderType::fragment)
    sid = glCreateShader(GL_FRAGMENT_SHADER);
  else
    return false;

  const char *cCode = code.c_str();
  glShaderSource(sid, 1, &cCode, NULL);
  glCompileShader(sid);

  int success;
  glGetShaderiv(sid, GL_COMPILE_STATUS, &success);

  if (!success) {
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
  } catch (std::ifstream::failure &exception) {
    return false;
  }
  return true;
}

void Shader::generateLocations() {
  std::unordered_map<int, const char *> locationMap = {
      {SHAD_LOC_OBJ_TYPE, "u_object_type"},
      {SHAD_LOC_MODEL_MAT, "u_model"},
      {SHAD_LOC_NORMAL_MAT, "u_normal_transform"},
      {SHAD_LOC_COLOR, "u_color"},

      {SHAD_LOC_VIEW_MAT, "u_view"},
      {SHAD_LOC_PROJECTION_MAT, "u_projection"},
      {SHAD_LOC_VIEW_POS, "u_view_pos"},

      {SHAD_LOC_MAT_AMBIENT, "u_material.ambient"},
      {SHAD_LOC_MAT_DIFFUSE, "u_material.diffuse"},
      {SHAD_LOC_MAT_SPECULAR, "u_material.specular"},
      {SHAD_LOC_MAT_SHININESS, "u_material.shininess"},
      {SHAD_LOC_FOG_FACTOR, "u_fog_factor"},
      {SHAD_LOC_FOG_COLOR, "u_fog_color"}};

  for (auto &entry : locationMap)
    locations[entry.first] = glGetUniformLocation(id, entry.second);

  std::string lightsArrName = "u_lights";
  std::unordered_map<int, std::string> lightLocationMap = {
      {SHAD_LIGHT_TYPE, "type"},
      {SHAD_LIGHT_POS, "position"},
      {SHAD_LIGHT_DIR, "direction"},
      {SHAD_LIGHT_CUTOFF, "cut_off"},
      {SHAD_LIGHT_ATTENUATION, "attenuation"},
      {SHAD_LIGHT_AMBIENT, "ambient"},
      {SHAD_LIGHT_DIFFUSE, "diffuse"},
      {SHAD_LIGHT_SPECULAR, "specular"}};

  int offset = SHAD_LIGHT_SECTION_BEGIN;
  for (int i = 0; i < SHAD_NR_LIGHTS; i++) {
    std::string label = lightsArrName + "[" + std::to_string(i) + "].";
    for (auto &entry : lightLocationMap) {
      int position = offset + i * SHAD_LIGHT_SECTION_LEN + entry.first;
      std::string name = label + entry.second;
      locations[position] = glGetUniformLocation(id, name.c_str());
    }
  }
}
