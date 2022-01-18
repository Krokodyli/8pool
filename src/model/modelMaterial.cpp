#include "modelMaterial.h"

ModelMaterial::ModelMaterial()
    : ambient(glm::vec3(0.0f)), diffuse(glm::vec3(0.0f)),
      specular(glm::vec3(0.0f)), shininess(1) {}

ModelMaterial::ModelMaterial(glm::vec3 ambient, glm::vec3 diffuse,
                             glm::vec3 specular, float shininess)
    : ambient(ambient), diffuse(diffuse), specular(specular),
      shininess(shininess) {}

const ModelMaterial ModelMaterials::plastic = {
    glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.55f, 0.55f, 0.55f),
    glm::vec3(0.7f, 0.7f, 0.7f), 32.0f};

const ModelMaterial ModelMaterials::fabric = {glm::vec3(0.00f, 0.00f, 0.0f),
                                            glm::vec3(0.7f, 0.7f, 0.7f),
                                            glm::vec3(0.0f, 0.0f, 0.0f), 128.0f};
