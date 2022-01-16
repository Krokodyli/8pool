#include "drawable.h"

void Drawable::initDrawable() {
  textureID = -1;
  meshID = -1;
  hasTexture = false;
}

int Drawable::getTextureID() {
  return textureID;
}

int Drawable::getMeshID() {
  return meshID;
}
