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
    glm::vec3(0.4f, 0.4f, 0.4f), 128.0f};

const ModelMaterial ModelMaterials::blackPlastic = {
    glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.55f, 0.55f, 0.55f),
    glm::vec3(0.8f, 0.8f, 0.8f), 128.0f};

const ModelMaterial ModelMaterials::fabric = {glm::vec3(0.1f, 0.1f, 0.1f),
                                            glm::vec3(0.5f, 0.5f, 0.5f),
                                            glm::vec3(0.0f, 0.0f, 0.0f), 128.0f};
