#include "modelMaterial.h"

ModelMaterial::ModelMaterial()
    : ambient(glm::vec3(0.0f)), diffuse(glm::vec3(0.0f)),
      specular(glm::vec3(0.0f)), shininess(1) {}

ModelMaterial::ModelMaterial(glm::vec3 ambient, glm::vec3 diffuse,
                             glm::vec3 specular, float shininess)
    : ambient(ambient), diffuse(diffuse), specular(specular),
      shininess(shininess) {}

const ModelMaterial ModelMaterials::gold = {glm::vec3(1.0f, 1.0f, 1.0f),
                                            glm::vec3(1.0f, 1.0f, 1.0f),
                                            glm::vec3(1.0f, 1.0f, 1.0f), 1.0f};
