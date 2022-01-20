#include "model.h"

Model::Model() : loaded(false) {}

Model::Model(unsigned int meshID, glm::vec3 color, ModelMaterial material)
    : loaded(true), lightSourceFlag(false), meshID(meshID), material(material),
      color(color), hasTexture(false) {}

Model::Model(unsigned int meshID, unsigned int textureID,
             ModelMaterial material)
    : loaded(true), lightSourceFlag(false), meshID(meshID), material(material),
      textureID(textureID), hasTexture(true) {}

bool Model::isLoaded() { return loaded; }
unsigned int Model::getMeshID() { return meshID; }
ModelMaterial Model::getMaterial() { return material; }

bool Model::isTextured() { return hasTexture; }
unsigned int Model::getTextureID() { return textureID; }
glm::vec3 Model::getColor() { return color; }
void Model::setColor(glm::vec3 value) { color = value; }
bool Model::isLightSource() { return lightSourceFlag; }
void Model::setLightSourceFlag(bool value) { lightSourceFlag = value; }
